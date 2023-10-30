# 如何使用
在doc目录下生成一个8G的随机文件模拟文件系统
`dd if=/dev/urandom of=./doc/myfilesystem bs=8M count=1024`
直接在项目目录下执行./run.sh

# 如何测试
在项目目录下执行./test.sh
将测试./testfile/src1G与./testfile/dst1G
将测试./testfile/src2G与./testfile/dst2G
将测试./testfile/src4G与./testfile/dst4G