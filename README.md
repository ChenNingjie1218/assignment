# 作业
作业的master分支，拉取这个分支然后新建分支做作业

# 生成私钥及公钥
openssl genpkey -algorithm RSA -out private_key.pem -pkeyopt rsa_keygen_bits:2048
openssl rsa -pubout -in private_key.pem -out public_key.pem
```
这将生成一个2048位的RSA私钥，并从私钥中提取公钥，并将私钥保存在private_key.pem文件中，将公钥保存在public_key.pem文件中。