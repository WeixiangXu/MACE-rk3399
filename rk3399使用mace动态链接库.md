## 从caffe转换模型
按照MACE官网教程操作即可，主要过程如下<br>
- 在你的主机（Linux）上配置好MACE
- 转换<br>
`python tools/converter.py convert --config=/home/xuweixiang/mace/xwx_for_boards/vgg.yml`<br>
其中vgg.yml的编写类似如下
```
library_name: model_need
target_abis: [arm64]
model_graph_format: file
model_data_format: file
models:
  vgg16:
    platform: caffe
    model_file_path: https://cnbj1.fds.api.xiaomi.com/mace/miai-models/vgg16/vgg16.prototxt
    model_sha256_checksum: 3fafb609587c0439f5fd1423086692c84b84029a954c08853a3bb6cf79b55c60
    weight_file_path: /home/xuweixiang/mace/xwx_for_benchmark/vgg16.caffemodel
    weight_sha256_checksum: b2cc45ad0d75d38ac25fabaf120637af5277b2dea149db197bf52c02d49bc219
    subgraphs:
      - input_tensors: data
        output_tensors: prob
        input_shapes: 1,224,224,3
        output_shapes: 1,1,1,1000
    runtime: cpu
    winograd: 0
```
- 得到的是.pb和.data文件
可参考两个我们当时的实验记录<br>
[实验记录1](https://github.com/RoyLJH/mace/blob/master/20190316.md)<br>
[实验记录2](https://github.com/WeixiangXu/mace/blob/master/my.md)<br>

## 在RK3399上使用编译好的MACE动态链接库
在RK3399上使用编译好的MACE动态链接库，搭建自己的网络。<br>
所需要的头文件和.so库已经编译好，可以直接调用。<br>
发送的是arrch64架构的库（适用于arm板子如rk3399），此外还有armv8/x86架构<br>

文件说明：
- armv8，里边是include和lib库
- build，cmake在这里编译
- include和src
- CMakeLists.txt 你需要在这里指向链接

mace_net.cpp的说明：
- 关注三个函数：1.构造函数MACENet::MACENet  2.加载模型MACENet::LoadModel  3.进行分类MACENet::Predict
- 修改cpu/gpu模式：string FLAGS_device = "GPU"; 可以改cpu gpu模式
- 可以参考main函数里给的step1234
- 模型类型参考model_type.hpp
- mymace.LoadModel("alexnet.pb","alexnet.data")这里的模型和参数文件是从caffe转换好的
- 我测的gpu时间：1.19021s  cpu时间：2.7776s（测20次取平均）
