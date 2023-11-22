package com.cache.grpc;

import static io.grpc.MethodDescriptor.generateFullMethodName;

/**
 */
@javax.annotation.Generated(
    value = "by gRPC proto compiler (version 1.59.0)",
    comments = "Source: Cache.proto")
@io.grpc.stub.annotations.GrpcGenerated
public final class KeyValueServiceGrpc {

  private KeyValueServiceGrpc() {}

  public static final java.lang.String SERVICE_NAME = "Cache.KeyValueService";

  // Static method descriptors that strictly reflect the proto.
  private static volatile io.grpc.MethodDescriptor<com.cache.grpc.KeyRequest,
      com.cache.grpc.KeyValueResponse> getGetValueMethod;

  @io.grpc.stub.annotations.RpcMethod(
      fullMethodName = SERVICE_NAME + '/' + "getValue",
      requestType = com.cache.grpc.KeyRequest.class,
      responseType = com.cache.grpc.KeyValueResponse.class,
      methodType = io.grpc.MethodDescriptor.MethodType.UNARY)
  public static io.grpc.MethodDescriptor<com.cache.grpc.KeyRequest,
      com.cache.grpc.KeyValueResponse> getGetValueMethod() {
    io.grpc.MethodDescriptor<com.cache.grpc.KeyRequest, com.cache.grpc.KeyValueResponse> getGetValueMethod;
    if ((getGetValueMethod = KeyValueServiceGrpc.getGetValueMethod) == null) {
      synchronized (KeyValueServiceGrpc.class) {
        if ((getGetValueMethod = KeyValueServiceGrpc.getGetValueMethod) == null) {
          KeyValueServiceGrpc.getGetValueMethod = getGetValueMethod =
              io.grpc.MethodDescriptor.<com.cache.grpc.KeyRequest, com.cache.grpc.KeyValueResponse>newBuilder()
              .setType(io.grpc.MethodDescriptor.MethodType.UNARY)
              .setFullMethodName(generateFullMethodName(SERVICE_NAME, "getValue"))
              .setSampledToLocalTracing(true)
              .setRequestMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                  com.cache.grpc.KeyRequest.getDefaultInstance()))
              .setResponseMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                  com.cache.grpc.KeyValueResponse.getDefaultInstance()))
              .setSchemaDescriptor(new KeyValueServiceMethodDescriptorSupplier("getValue"))
              .build();
        }
      }
    }
    return getGetValueMethod;
  }

  private static volatile io.grpc.MethodDescriptor<com.cache.grpc.KeyValueRequest,
      com.cache.grpc.EmptyResponse> getPutValueMethod;

  @io.grpc.stub.annotations.RpcMethod(
      fullMethodName = SERVICE_NAME + '/' + "putValue",
      requestType = com.cache.grpc.KeyValueRequest.class,
      responseType = com.cache.grpc.EmptyResponse.class,
      methodType = io.grpc.MethodDescriptor.MethodType.UNARY)
  public static io.grpc.MethodDescriptor<com.cache.grpc.KeyValueRequest,
      com.cache.grpc.EmptyResponse> getPutValueMethod() {
    io.grpc.MethodDescriptor<com.cache.grpc.KeyValueRequest, com.cache.grpc.EmptyResponse> getPutValueMethod;
    if ((getPutValueMethod = KeyValueServiceGrpc.getPutValueMethod) == null) {
      synchronized (KeyValueServiceGrpc.class) {
        if ((getPutValueMethod = KeyValueServiceGrpc.getPutValueMethod) == null) {
          KeyValueServiceGrpc.getPutValueMethod = getPutValueMethod =
              io.grpc.MethodDescriptor.<com.cache.grpc.KeyValueRequest, com.cache.grpc.EmptyResponse>newBuilder()
              .setType(io.grpc.MethodDescriptor.MethodType.UNARY)
              .setFullMethodName(generateFullMethodName(SERVICE_NAME, "putValue"))
              .setSampledToLocalTracing(true)
              .setRequestMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                  com.cache.grpc.KeyValueRequest.getDefaultInstance()))
              .setResponseMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                  com.cache.grpc.EmptyResponse.getDefaultInstance()))
              .setSchemaDescriptor(new KeyValueServiceMethodDescriptorSupplier("putValue"))
              .build();
        }
      }
    }
    return getPutValueMethod;
  }

  private static volatile io.grpc.MethodDescriptor<com.cache.grpc.KeyRequest,
      com.cache.grpc.NumberResponse> getRemoveKeyMethod;

  @io.grpc.stub.annotations.RpcMethod(
      fullMethodName = SERVICE_NAME + '/' + "removeKey",
      requestType = com.cache.grpc.KeyRequest.class,
      responseType = com.cache.grpc.NumberResponse.class,
      methodType = io.grpc.MethodDescriptor.MethodType.UNARY)
  public static io.grpc.MethodDescriptor<com.cache.grpc.KeyRequest,
      com.cache.grpc.NumberResponse> getRemoveKeyMethod() {
    io.grpc.MethodDescriptor<com.cache.grpc.KeyRequest, com.cache.grpc.NumberResponse> getRemoveKeyMethod;
    if ((getRemoveKeyMethod = KeyValueServiceGrpc.getRemoveKeyMethod) == null) {
      synchronized (KeyValueServiceGrpc.class) {
        if ((getRemoveKeyMethod = KeyValueServiceGrpc.getRemoveKeyMethod) == null) {
          KeyValueServiceGrpc.getRemoveKeyMethod = getRemoveKeyMethod =
              io.grpc.MethodDescriptor.<com.cache.grpc.KeyRequest, com.cache.grpc.NumberResponse>newBuilder()
              .setType(io.grpc.MethodDescriptor.MethodType.UNARY)
              .setFullMethodName(generateFullMethodName(SERVICE_NAME, "removeKey"))
              .setSampledToLocalTracing(true)
              .setRequestMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                  com.cache.grpc.KeyRequest.getDefaultInstance()))
              .setResponseMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                  com.cache.grpc.NumberResponse.getDefaultInstance()))
              .setSchemaDescriptor(new KeyValueServiceMethodDescriptorSupplier("removeKey"))
              .build();
        }
      }
    }
    return getRemoveKeyMethod;
  }

  /**
   * Creates a new async stub that supports all call types for the service
   */
  public static KeyValueServiceStub newStub(io.grpc.Channel channel) {
    io.grpc.stub.AbstractStub.StubFactory<KeyValueServiceStub> factory =
      new io.grpc.stub.AbstractStub.StubFactory<KeyValueServiceStub>() {
        @java.lang.Override
        public KeyValueServiceStub newStub(io.grpc.Channel channel, io.grpc.CallOptions callOptions) {
          return new KeyValueServiceStub(channel, callOptions);
        }
      };
    return KeyValueServiceStub.newStub(factory, channel);
  }

  /**
   * Creates a new blocking-style stub that supports unary and streaming output calls on the service
   */
  public static KeyValueServiceBlockingStub newBlockingStub(
      io.grpc.Channel channel) {
    io.grpc.stub.AbstractStub.StubFactory<KeyValueServiceBlockingStub> factory =
      new io.grpc.stub.AbstractStub.StubFactory<KeyValueServiceBlockingStub>() {
        @java.lang.Override
        public KeyValueServiceBlockingStub newStub(io.grpc.Channel channel, io.grpc.CallOptions callOptions) {
          return new KeyValueServiceBlockingStub(channel, callOptions);
        }
      };
    return KeyValueServiceBlockingStub.newStub(factory, channel);
  }

  /**
   * Creates a new ListenableFuture-style stub that supports unary calls on the service
   */
  public static KeyValueServiceFutureStub newFutureStub(
      io.grpc.Channel channel) {
    io.grpc.stub.AbstractStub.StubFactory<KeyValueServiceFutureStub> factory =
      new io.grpc.stub.AbstractStub.StubFactory<KeyValueServiceFutureStub>() {
        @java.lang.Override
        public KeyValueServiceFutureStub newStub(io.grpc.Channel channel, io.grpc.CallOptions callOptions) {
          return new KeyValueServiceFutureStub(channel, callOptions);
        }
      };
    return KeyValueServiceFutureStub.newStub(factory, channel);
  }

  /**
   */
  public interface AsyncService {

    /**
     */
    default void getValue(com.cache.grpc.KeyRequest request,
        io.grpc.stub.StreamObserver<com.cache.grpc.KeyValueResponse> responseObserver) {
      io.grpc.stub.ServerCalls.asyncUnimplementedUnaryCall(getGetValueMethod(), responseObserver);
    }

    /**
     */
    default void putValue(com.cache.grpc.KeyValueRequest request,
        io.grpc.stub.StreamObserver<com.cache.grpc.EmptyResponse> responseObserver) {
      io.grpc.stub.ServerCalls.asyncUnimplementedUnaryCall(getPutValueMethod(), responseObserver);
    }

    /**
     */
    default void removeKey(com.cache.grpc.KeyRequest request,
        io.grpc.stub.StreamObserver<com.cache.grpc.NumberResponse> responseObserver) {
      io.grpc.stub.ServerCalls.asyncUnimplementedUnaryCall(getRemoveKeyMethod(), responseObserver);
    }
  }

  /**
   * Base class for the server implementation of the service KeyValueService.
   */
  public static abstract class KeyValueServiceImplBase
      implements io.grpc.BindableService, AsyncService {

    @java.lang.Override public final io.grpc.ServerServiceDefinition bindService() {
      return KeyValueServiceGrpc.bindService(this);
    }
  }

  /**
   * A stub to allow clients to do asynchronous rpc calls to service KeyValueService.
   */
  public static final class KeyValueServiceStub
      extends io.grpc.stub.AbstractAsyncStub<KeyValueServiceStub> {
    private KeyValueServiceStub(
        io.grpc.Channel channel, io.grpc.CallOptions callOptions) {
      super(channel, callOptions);
    }

    @java.lang.Override
    protected KeyValueServiceStub build(
        io.grpc.Channel channel, io.grpc.CallOptions callOptions) {
      return new KeyValueServiceStub(channel, callOptions);
    }

    /**
     */
    public void getValue(com.cache.grpc.KeyRequest request,
        io.grpc.stub.StreamObserver<com.cache.grpc.KeyValueResponse> responseObserver) {
      io.grpc.stub.ClientCalls.asyncUnaryCall(
          getChannel().newCall(getGetValueMethod(), getCallOptions()), request, responseObserver);
    }

    /**
     */
    public void putValue(com.cache.grpc.KeyValueRequest request,
        io.grpc.stub.StreamObserver<com.cache.grpc.EmptyResponse> responseObserver) {
      io.grpc.stub.ClientCalls.asyncUnaryCall(
          getChannel().newCall(getPutValueMethod(), getCallOptions()), request, responseObserver);
    }

    /**
     */
    public void removeKey(com.cache.grpc.KeyRequest request,
        io.grpc.stub.StreamObserver<com.cache.grpc.NumberResponse> responseObserver) {
      io.grpc.stub.ClientCalls.asyncUnaryCall(
          getChannel().newCall(getRemoveKeyMethod(), getCallOptions()), request, responseObserver);
    }
  }

  /**
   * A stub to allow clients to do synchronous rpc calls to service KeyValueService.
   */
  public static final class KeyValueServiceBlockingStub
      extends io.grpc.stub.AbstractBlockingStub<KeyValueServiceBlockingStub> {
    private KeyValueServiceBlockingStub(
        io.grpc.Channel channel, io.grpc.CallOptions callOptions) {
      super(channel, callOptions);
    }

    @java.lang.Override
    protected KeyValueServiceBlockingStub build(
        io.grpc.Channel channel, io.grpc.CallOptions callOptions) {
      return new KeyValueServiceBlockingStub(channel, callOptions);
    }

    /**
     */
    public com.cache.grpc.KeyValueResponse getValue(com.cache.grpc.KeyRequest request) {
      return io.grpc.stub.ClientCalls.blockingUnaryCall(
          getChannel(), getGetValueMethod(), getCallOptions(), request);
    }

    /**
     */
    public com.cache.grpc.EmptyResponse putValue(com.cache.grpc.KeyValueRequest request) {
      return io.grpc.stub.ClientCalls.blockingUnaryCall(
          getChannel(), getPutValueMethod(), getCallOptions(), request);
    }

    /**
     */
    public com.cache.grpc.NumberResponse removeKey(com.cache.grpc.KeyRequest request) {
      return io.grpc.stub.ClientCalls.blockingUnaryCall(
          getChannel(), getRemoveKeyMethod(), getCallOptions(), request);
    }
  }

  /**
   * A stub to allow clients to do ListenableFuture-style rpc calls to service KeyValueService.
   */
  public static final class KeyValueServiceFutureStub
      extends io.grpc.stub.AbstractFutureStub<KeyValueServiceFutureStub> {
    private KeyValueServiceFutureStub(
        io.grpc.Channel channel, io.grpc.CallOptions callOptions) {
      super(channel, callOptions);
    }

    @java.lang.Override
    protected KeyValueServiceFutureStub build(
        io.grpc.Channel channel, io.grpc.CallOptions callOptions) {
      return new KeyValueServiceFutureStub(channel, callOptions);
    }

    /**
     */
    public com.google.common.util.concurrent.ListenableFuture<com.cache.grpc.KeyValueResponse> getValue(
        com.cache.grpc.KeyRequest request) {
      return io.grpc.stub.ClientCalls.futureUnaryCall(
          getChannel().newCall(getGetValueMethod(), getCallOptions()), request);
    }

    /**
     */
    public com.google.common.util.concurrent.ListenableFuture<com.cache.grpc.EmptyResponse> putValue(
        com.cache.grpc.KeyValueRequest request) {
      return io.grpc.stub.ClientCalls.futureUnaryCall(
          getChannel().newCall(getPutValueMethod(), getCallOptions()), request);
    }

    /**
     */
    public com.google.common.util.concurrent.ListenableFuture<com.cache.grpc.NumberResponse> removeKey(
        com.cache.grpc.KeyRequest request) {
      return io.grpc.stub.ClientCalls.futureUnaryCall(
          getChannel().newCall(getRemoveKeyMethod(), getCallOptions()), request);
    }
  }

  private static final int METHODID_GET_VALUE = 0;
  private static final int METHODID_PUT_VALUE = 1;
  private static final int METHODID_REMOVE_KEY = 2;

  private static final class MethodHandlers<Req, Resp> implements
      io.grpc.stub.ServerCalls.UnaryMethod<Req, Resp>,
      io.grpc.stub.ServerCalls.ServerStreamingMethod<Req, Resp>,
      io.grpc.stub.ServerCalls.ClientStreamingMethod<Req, Resp>,
      io.grpc.stub.ServerCalls.BidiStreamingMethod<Req, Resp> {
    private final AsyncService serviceImpl;
    private final int methodId;

    MethodHandlers(AsyncService serviceImpl, int methodId) {
      this.serviceImpl = serviceImpl;
      this.methodId = methodId;
    }

    @java.lang.Override
    @java.lang.SuppressWarnings("unchecked")
    public void invoke(Req request, io.grpc.stub.StreamObserver<Resp> responseObserver) {
      switch (methodId) {
        case METHODID_GET_VALUE:
          serviceImpl.getValue((com.cache.grpc.KeyRequest) request,
              (io.grpc.stub.StreamObserver<com.cache.grpc.KeyValueResponse>) responseObserver);
          break;
        case METHODID_PUT_VALUE:
          serviceImpl.putValue((com.cache.grpc.KeyValueRequest) request,
              (io.grpc.stub.StreamObserver<com.cache.grpc.EmptyResponse>) responseObserver);
          break;
        case METHODID_REMOVE_KEY:
          serviceImpl.removeKey((com.cache.grpc.KeyRequest) request,
              (io.grpc.stub.StreamObserver<com.cache.grpc.NumberResponse>) responseObserver);
          break;
        default:
          throw new AssertionError();
      }
    }

    @java.lang.Override
    @java.lang.SuppressWarnings("unchecked")
    public io.grpc.stub.StreamObserver<Req> invoke(
        io.grpc.stub.StreamObserver<Resp> responseObserver) {
      switch (methodId) {
        default:
          throw new AssertionError();
      }
    }
  }

  public static final io.grpc.ServerServiceDefinition bindService(AsyncService service) {
    return io.grpc.ServerServiceDefinition.builder(getServiceDescriptor())
        .addMethod(
          getGetValueMethod(),
          io.grpc.stub.ServerCalls.asyncUnaryCall(
            new MethodHandlers<
              com.cache.grpc.KeyRequest,
              com.cache.grpc.KeyValueResponse>(
                service, METHODID_GET_VALUE)))
        .addMethod(
          getPutValueMethod(),
          io.grpc.stub.ServerCalls.asyncUnaryCall(
            new MethodHandlers<
              com.cache.grpc.KeyValueRequest,
              com.cache.grpc.EmptyResponse>(
                service, METHODID_PUT_VALUE)))
        .addMethod(
          getRemoveKeyMethod(),
          io.grpc.stub.ServerCalls.asyncUnaryCall(
            new MethodHandlers<
              com.cache.grpc.KeyRequest,
              com.cache.grpc.NumberResponse>(
                service, METHODID_REMOVE_KEY)))
        .build();
  }

  private static abstract class KeyValueServiceBaseDescriptorSupplier
      implements io.grpc.protobuf.ProtoFileDescriptorSupplier, io.grpc.protobuf.ProtoServiceDescriptorSupplier {
    KeyValueServiceBaseDescriptorSupplier() {}

    @java.lang.Override
    public com.google.protobuf.Descriptors.FileDescriptor getFileDescriptor() {
      return com.cache.grpc.CacheProto.getDescriptor();
    }

    @java.lang.Override
    public com.google.protobuf.Descriptors.ServiceDescriptor getServiceDescriptor() {
      return getFileDescriptor().findServiceByName("KeyValueService");
    }
  }

  private static final class KeyValueServiceFileDescriptorSupplier
      extends KeyValueServiceBaseDescriptorSupplier {
    KeyValueServiceFileDescriptorSupplier() {}
  }

  private static final class KeyValueServiceMethodDescriptorSupplier
      extends KeyValueServiceBaseDescriptorSupplier
      implements io.grpc.protobuf.ProtoMethodDescriptorSupplier {
    private final java.lang.String methodName;

    KeyValueServiceMethodDescriptorSupplier(java.lang.String methodName) {
      this.methodName = methodName;
    }

    @java.lang.Override
    public com.google.protobuf.Descriptors.MethodDescriptor getMethodDescriptor() {
      return getServiceDescriptor().findMethodByName(methodName);
    }
  }

  private static volatile io.grpc.ServiceDescriptor serviceDescriptor;

  public static io.grpc.ServiceDescriptor getServiceDescriptor() {
    io.grpc.ServiceDescriptor result = serviceDescriptor;
    if (result == null) {
      synchronized (KeyValueServiceGrpc.class) {
        result = serviceDescriptor;
        if (result == null) {
          serviceDescriptor = result = io.grpc.ServiceDescriptor.newBuilder(SERVICE_NAME)
              .setSchemaDescriptor(new KeyValueServiceFileDescriptorSupplier())
              .addMethod(getGetValueMethod())
              .addMethod(getPutValueMethod())
              .addMethod(getRemoveKeyMethod())
              .build();
        }
      }
    }
    return result;
  }
}
