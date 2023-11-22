package org.example;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ConfigurableApplicationContext;
import org.springframework.core.env.Environment;

import java.io.IOException;

@SpringBootApplication
public class CacheServer {
    public static void main(String[] args) throws IOException, InterruptedException {
        ConfigurableApplicationContext run = SpringApplication.run(CacheServer.class, args);
        GrpcServer grpcServer = (GrpcServer) run.getBean("grpcServer");
        GrpcServer.gRPCport = run.getEnvironment().getProperty("rpc.port");
//        GrpcServer.gRPCport = environment.getProperty("rpc.port");
        grpcServer.start();
        grpcServer.blockUntilShutdown();

    }
}




