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
- rk3399
- CPU 223ms
- GPU 883ms(detection output这一层的操作mace官方并没有gpu的优化版本)
- 如何更改CPU、GPU模式，见之前的文档
