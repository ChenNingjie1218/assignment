// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Cache.proto

package com.cache.grpc;

public final class CacheProto {
  private CacheProto() {}
  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistryLite registry) {
  }

  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistry registry) {
    registerAllExtensions(
        (com.google.protobuf.ExtensionRegistryLite) registry);
  }
  static final com.google.protobuf.Descriptors.Descriptor
    internal_static_Cache_KeyRequest_descriptor;
  static final 
    com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
      internal_static_Cache_KeyRequest_fieldAccessorTable;
  static final com.google.protobuf.Descriptors.Descriptor
    internal_static_Cache_KeyValueResponse_descriptor;
  static final 
    com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
      internal_static_Cache_KeyValueResponse_fieldAccessorTable;
  static final com.google.protobuf.Descriptors.Descriptor
    internal_static_Cache_KeyValueRequest_descriptor;
  static final 
    com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
      internal_static_Cache_KeyValueRequest_fieldAccessorTable;
  static final com.google.protobuf.Descriptors.Descriptor
    internal_static_Cache_EmptyResponse_descriptor;
  static final 
    com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
      internal_static_Cache_EmptyResponse_fieldAccessorTable;
  static final com.google.protobuf.Descriptors.Descriptor
    internal_static_Cache_NumberResponse_descriptor;
  static final 
    com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
      internal_static_Cache_NumberResponse_fieldAccessorTable;

  public static com.google.protobuf.Descriptors.FileDescriptor
      getDescriptor() {
    return descriptor;
  }
  private static  com.google.protobuf.Descriptors.FileDescriptor
      descriptor;
  static {
    java.lang.String[] descriptorData = {
      "\n\013Cache.proto\022\005Cache\"\031\n\nKeyRequest\022\013\n\003ke" +
      "y\030\001 \001(\t\".\n\020KeyValueResponse\022\013\n\003key\030\001 \001(\t" +
      "\022\r\n\005value\030\002 \001(\t\"-\n\017KeyValueRequest\022\013\n\003ke" +
      "y\030\001 \001(\t\022\r\n\005value\030\002 \001(\t\"\017\n\rEmptyResponse\"" +
      " \n\016NumberResponse\022\016\n\006number\030\001 \001(\0052\272\001\n\017Ke" +
      "yValueService\0226\n\010getValue\022\021.Cache.KeyReq" +
      "uest\032\027.Cache.KeyValueResponse\0228\n\010putValu" +
      "e\022\026.Cache.KeyValueRequest\032\024.Cache.EmptyR" +
      "esponse\0225\n\tremoveKey\022\021.Cache.KeyRequest\032" +
      "\025.Cache.NumberResponseB\036\n\016com.cache.grpc" +
      "B\nCacheProtoP\001b\006proto3"
    };
    descriptor = com.google.protobuf.Descriptors.FileDescriptor
      .internalBuildGeneratedFileFrom(descriptorData,
        new com.google.protobuf.Descriptors.FileDescriptor[] {
        });
    internal_static_Cache_KeyRequest_descriptor =
      getDescriptor().getMessageTypes().get(0);
    internal_static_Cache_KeyRequest_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessageV3.FieldAccessorTable(
        internal_static_Cache_KeyRequest_descriptor,
        new java.lang.String[] { "Key", });
    internal_static_Cache_KeyValueResponse_descriptor =
      getDescriptor().getMessageTypes().get(1);
    internal_static_Cache_KeyValueResponse_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessageV3.FieldAccessorTable(
        internal_static_Cache_KeyValueResponse_descriptor,
        new java.lang.String[] { "Key", "Value", });
    internal_static_Cache_KeyValueRequest_descriptor =
      getDescriptor().getMessageTypes().get(2);
    internal_static_Cache_KeyValueRequest_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessageV3.FieldAccessorTable(
        internal_static_Cache_KeyValueRequest_descriptor,
        new java.lang.String[] { "Key", "Value", });
    internal_static_Cache_EmptyResponse_descriptor =
      getDescriptor().getMessageTypes().get(3);
    internal_static_Cache_EmptyResponse_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessageV3.FieldAccessorTable(
        internal_static_Cache_EmptyResponse_descriptor,
        new java.lang.String[] { });
    internal_static_Cache_NumberResponse_descriptor =
      getDescriptor().getMessageTypes().get(4);
    internal_static_Cache_NumberResponse_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessageV3.FieldAccessorTable(
        internal_static_Cache_NumberResponse_descriptor,
        new java.lang.String[] { "Number", });
  }

  // @@protoc_insertion_point(outer_class_scope)
}
