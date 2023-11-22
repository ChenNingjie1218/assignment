package org.example;

import com.cache.grpc.*;
import com.cache.grpc.EmptyResponse;
import com.cache.grpc.KeyRequest;
import com.cache.grpc.KeyValueRequest;
import com.cache.grpc.KeyValueResponse;
import io.grpc.Server;
import io.grpc.ServerBuilder;
import io.grpc.stub.StreamObserver;
import org.springframework.stereotype.Component;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
@Component
public class GrpcServer {
    private Server server;
    private static final int BASE_PORT = 6749;
    private static volatile int currentPort = BASE_PORT;
    public static Map<String, String> keyValue = new HashMap<>();

    public static String gRPCport;
    public void start() throws IOException {
//        int port = getNextPort();
        System.out.println(gRPCport);
        int port = Integer.parseInt(gRPCport);
        server = ServerBuilder.forPort(port)
                .addService(new KeyValueServiceImpl())
                .build()
                .start();

        System.out.println("gRPC Server started, listening on port " + port);

        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            System.err.println("*** Shutting down gRPC server since JVM is shutting down");
            stop();
            System.err.println("*** gRPC Server shut down");
        }));
    }

    private void stop() {
        if (server != null) {
            server.shutdown();
        }
    }

    public void blockUntilShutdown() throws InterruptedException {
        if (server != null) {
            server.awaitTermination();
        }
    }

    private static synchronized int getNextPort() {
        return currentPort++;
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        final GrpcServer server = new GrpcServer();
        gRPCport = args[0];
        server.start();
        server.blockUntilShutdown();
    }

    static class KeyValueServiceImpl extends KeyValueServiceGrpc.KeyValueServiceImplBase {
        @Override
        public void getValue(KeyRequest request, StreamObserver<KeyValueResponse> responseObserver) {
            String key = request.getKey();
            KeyValueResponse response = null;
            if (keyValue.containsKey(key)) {
                String value = keyValue.get(key);
//                Object value = keyValue.get(key);
//                String stringValue = value.toString();
                response = KeyValueResponse.newBuilder()
                        .setKey(key)
                        .setValue(value)
                        .build();
            }

            responseObserver.onNext(response);
            responseObserver.onCompleted();
        }


        @Override
        public void putValue(KeyValueRequest request, StreamObserver<EmptyResponse> responseObserver){
            keyValue.put(request.getKey(), request.getValue());
            EmptyResponse response = EmptyResponse.newBuilder().build();
            responseObserver.onNext(response);
            responseObserver.onCompleted();
        }

        @Override
        public void removeKey(KeyRequest request, StreamObserver<com.cache.grpc.NumberResponse> responseObserver){
            int num = 1;
            if(keyValue.remove(request.getKey()) == null){
                num = 0;
            }
            NumberResponse response = NumberResponse
                    .newBuilder()
                    .setNumber(num)
                    .build();
            responseObserver.onNext(response);
            responseObserver.onCompleted();
        }
    }
}
