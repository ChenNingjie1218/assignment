FROM ubuntu:20.04
LABEL authors="202352080412-ChenNingjie"
WORKDIR /app

COPY . .

RUN apt-get update &&\
    apt-get install -y openjdk-11-jdk  curl \
    && rm -rf /var/lib/apt/lists/*

RUN curl -fsSL -o /tmp/apache-maven.tar.gz https://dlcdn.apache.org/maven/maven-3/3.9.5/binaries/apache-maven-3.9.5-bin.tar.gz && \
        tar -xzf /tmp/apache-maven.tar.gz -C /opt && \
        ln -s /opt/apache-maven-3.9.5 /opt/maven && \
        rm /tmp/apache-maven.tar.gz

# 配置环境变量
ENV PATH="/opt/maven/bin:$PATH"

#RUN mvn clean package -DoutputDirectory=./
RUN mvn clean package

RUN cp ./target/app-1.0-SNAPSHOT.jar /usr/local/bin/
RUN cd target && ls -l
RUN chmod 755 /usr/local/bin/app-1.0-SNAPSHOT.jar

CMD ["java", "-jar", "/usr/local/bin/app.jar"]
