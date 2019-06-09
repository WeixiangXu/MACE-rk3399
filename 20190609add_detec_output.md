## 输出格式
- 定义在base_net.hpp中
```
struct BBox {
  float xmin;
  float ymin;
  float xmax;
  float ymax;
  int label;
  float confidence;
};
```

## 图片预处理
- include/preprocess_factory.hpp

## 合并detection_output
- src/mace_net.cpp

## 时间测试
- rk3399，mobilenetv1_ssd
- CPU 223ms
- GPU 450ms 
- 如何更改CPU、GPU模式，见之前的文档

- 注意：gpu测试一次耗时约为1000+ms，但一次性测50次取平均约为450ms。（初始化原因导致第一次测试耗时较长）

## how to run
- 准备一张图"pic1.jpg"在build下
- ssd_mobilenet_v1.data和ssd_mobilenet_v1.pb已经转换好在build下
- cmake，make
- ./mace_on_boards
