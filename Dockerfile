FROM ubuntu:20.04
LABEL authors="202352080412-ChenNingjie"
WORKDIR /

RUN apt-get update &&\
    apt-get install -y openjdk-21-jdk

RUN curl -fsSL -o /tmp/apache-maven.tar.gz https://dlcdn.apache.org/maven/maven-3/3.9.5/binaries/apache-maven-3.9.5-bin.tar.gz && \
        tar -xzf /tmp/apache-maven.tar.gz -C /opt && \
        ln -s /opt/apache-maven-3.9.5 /opt/maven && \
        rm /tmp/apache-maven.tar.gz \

COPY ./settings.xml /opt/maven/conf/

# 配置环境变量
ENV PATH="/opt/maven/bin:$PATH"

#RUN mvn clean package -DoutputDirectory=./
RUN mvn clean
RUN mvn package -f /usr/server/pom.xml
RUN cp ./target/DistributedSystem-1.0-SNAPSHOT.jar /usr/server/
RUN chmod 755 /usr/server/DistributedSystem-1.0-SNAPSHOT.jar

CMD ["java", "-jar", "/usr/server/DistributedSystem-1.0-SNAPSHOT.jar"]
