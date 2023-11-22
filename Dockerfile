FROM ubuntu:20.04
LABEL authors="202352080412-ChenNingjie"
WORKDIR /app

COPY cacheserver.jar /app

CMD ["java", "-jar", "cacheserver.jar"]

ENTRYPOINT ["top", "-b"]