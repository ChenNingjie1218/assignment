package org.example;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import java.io.IOException;

@SpringBootApplication
public class CacheServer {

    public static void main(String[] args) throws IOException, InterruptedException {
        SpringApplication.run(CacheServer.class, args);
        GrpcServer.main(args);
    }
}




