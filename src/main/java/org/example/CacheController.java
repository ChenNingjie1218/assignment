package org.example;

import com.cache.grpc.*;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import io.grpc.ManagedChannel;
import io.grpc.ManagedChannelBuilder;
import org.json.JSONObject;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.TimeUnit;

@RestController
@RequestMapping("/")
public class CacheController {
    private ManagedChannel channel;
    private KeyValueServiceGrpc.KeyValueServiceBlockingStub blockingStub;
    int[] rpc_port = new int[]{6749,6750,6751};
    public void connect(String host, int port){
        //初始化连接
        channel = ManagedChannelBuilder.forAddress(host, port)
                .usePlaintext()
                .build();
        //初始化远程服务Stub
        blockingStub = KeyValueServiceGrpc.newBlockingStub(channel);
    }

    public void shutdown() throws InterruptedException {
        //关闭连接
        channel.shutdown().awaitTermination(5, TimeUnit.SECONDS);
    }


    // -------------------------------- http ---------------------------------------


    @GetMapping("/{key}")
    public ResponseEntity<Map<String, Object>> getValue(@PathVariable String key) throws InterruptedException{
        int id = key.length() % 3;
//        connect("127.0.0.1",rpc_port[id]);
        connect("127.0.0.1",rpc_port[0]);
        System.out.println(rpc_port[0]);
        KeyRequest request = KeyRequest.newBuilder().setKey(key).build();
        KeyValueResponse response = blockingStub.getValue(request);
        shutdown();
        if(response.getValue().isEmpty()){
            return ResponseEntity.notFound().build();
        }else{
            Map<String, Object> result = new HashMap<>();
//            JSONObject result = new JSONObject();
            // 创建 ObjectMapper 实例
            ObjectMapper objectMapper = new ObjectMapper();
            try {
                Object value = objectMapper.readValue(response.getValue(), Object.class);
                result.put(response.getKey(), value);
            } catch (JsonProcessingException e) {
                throw new RuntimeException(e);
            }
//            result.put(response.getKey(),response.getValue()+'\n');
            System.out.println("result:"+result);
            return ResponseEntity.ok(result);
        }

    }

    @PostMapping("/")
    public void setValue(@RequestBody String jsonString) throws InterruptedException {
        // 创建 ObjectMapper 实例
        ObjectMapper objectMapper = new ObjectMapper();
        try {
            // 将 JSON 字符串转换为 Map 对象
            Map<String, Object> dataMap = objectMapper.readValue(jsonString, Map.class);
            for (String key : dataMap.keySet()){
                Object value = dataMap.get(key);
                String stringValue = objectMapper.writeValueAsString(value);
                int id = key.length() % 3;
//            connect("127.0.0.1",rpc_port[id]);
                connect("127.0.0.1",rpc_port[0]);
                KeyValueRequest request = KeyValueRequest.newBuilder()
                        .setKey(key)
                        .setValue(stringValue)
                        .build();
                blockingStub.putValue(request);
                shutdown();
                System.out.println("设置成功");
            }

        } catch (IOException e) {
            e.printStackTrace();
        }

//        JSONObject jsonObject = new JSONObject(jsonString);
//        for (String key : jsonObject.keySet()){
//            Object value = jsonObject.get(key);
//            String stringValue = value.toString();
//            int id = key.length() % 3;
////            connect("127.0.0.1",rpc_port[id]);
//            connect("127.0.0.1",rpc_port[0]);
//            KeyValueRequest request = KeyValueRequest.newBuilder()
//                    .setKey(key)
//                    .setValue(stringValue)
//                    .build();
//            blockingStub.putValue(request);
//            shutdown();
//            System.out.println("设置成功");
//        }
    }

    @DeleteMapping("/{key}")
    public ResponseEntity<Integer> removeValue(@PathVariable String key) throws InterruptedException {
        int id = key.length() % 3;
//        connect("127.0.0.1",rpc_port[id]);
        connect("127.0.0.1",rpc_port[0]);
        KeyRequest request = KeyRequest.newBuilder().setKey(key).build();
        NumberResponse response = blockingStub.removeKey(request);
        shutdown();
        return ResponseEntity.ok(response.getNumber());
    }
}
