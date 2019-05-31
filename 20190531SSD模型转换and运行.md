## 目标
在RK3399上测试MACE运行ssd的时间

## 0.很乱的备忘（可以无视这一部分直接跳到1.模型转换）
- model_name: "mobile1_ssd" 关键，input shape要根据模型名字

- 检测和分类的输出略有不同，现在需要找到mace.cc里是怎么跑的
```
      - input_tensors:
          - data
        input_shapes:
          - 1,300,300,3
        output_tensors:
          - mbox_loc
          - mbox_conf_flatten
          - mbox_priorbox
        output_shapes:
          - 1,7668
          - 1,40257
          - 1,2,7668
```
- 在mace_net.cpp里float*MACENet::Run下，推断output_shape

- 官方说“In order to facilitate model optimization, we use the node "mbox_loc", "mbox_conf_flatten", "mbox_priorbox" as output. For the detection output layer, you can refer to detection_output.cc.”
- 也就是说它们的输出不是最后的检测框，而是detection_output上一层的三个分支

```
* Run 'ssd_mobilenet_v1' with round=1, restart_round=1, tuning=False, out_of_range_check=False, omp_num_threads=(-1,), cpu_affinity_policy=(1,), gpu_perf_hint=(3,), gpu_priority_hint=(3,)
Push builds/ssd-mobilenet-v1/_tmp/ssd_mobilenet_v1/f54c48d7f3efd2557cf6357f96c7916c/RockchipRK3399FireflyBoard_RK3399/arm64/model_input_data to /tmp/data/mace_run
Push builds/ssd-mobilenet-v1/model/ssd_mobilenet_v1.data to /tmp/data/mace_run
Push third_party/nnlib/libhexagon_controller.so to /tmp/data/mace_run
Push builds/ssd-mobilenet-v1/model/ssd_mobilenet_v1.pb to /tmp/data/mace_run/ssd_mobilenet_v1.pb
Push builds/ssd-mobilenet-v1/_tmp/arm64/mace_run_static to /tmp/data/mace_run
Push /tmp/cmd_file-ssd_mobilenet_v1-1559272506.76 to /tmp/data/mace_run/cmd_file-ssd_mobilenet_v1-1559272506.76
I mace/tools/validation/mace_run.cc:450] model name: ssd_mobilenet_v1
I mace/tools/validation/mace_run.cc:451] mace version: v0.10.0-30-g858dda5-20190531
I mace/tools/validation/mace_run.cc:452] input node: data
I mace/tools/validation/mace_run.cc:453] input shape: 1,300,300,3
I mace/tools/validation/mace_run.cc:454] output node: mbox_loc,mbox_conf_flatten,mbox_priorbox
I mace/tools/validation/mace_run.cc:455] output shape: 1,1,1,7668:1,40257,1:1,2,7668
I mace/tools/validation/mace_run.cc:456] input_file: /tmp/data/mace_run/model_input
I mace/tools/validation/mace_run.cc:457] output_file: /tmp/data/mace_run/model_out
I mace/tools/validation/mace_run.cc:458] model_data_file: /tmp/data/mace_run/ssd_mobilenet_v1.data
I mace/tools/validation/mace_run.cc:459] model_file: /tmp/data/mace_run/ssd_mobilenet_v1.pb
I mace/tools/validation/mace_run.cc:460] device: CPU
I mace/tools/validation/mace_run.cc:461] round: 1
I mace/tools/validation/mace_run.cc:462] restart_round: 1
I mace/tools/validation/mace_run.cc:463] gpu_perf_hint: 3
I mace/tools/validation/mace_run.cc:464] gpu_priority_hint: 3
I mace/tools/validation/mace_run.cc:465] omp_num_threads: -1
I mace/tools/validation/mace_run.cc:466] cpu_affinity_policy: 1
I mace/tools/validation/mace_run.cc:489] restart round 0
I mace/libmace/mace.cc:785] Create MaceEngine from model graph proto and weights data
I mace/libmace/mace.cc:432] Creating MaceEngine, MACE version: v0.10.0-30-g858dda5-20190531
I mace/libmace/mace.cc:464] Initializing MaceEngine
I mace/tools/validation/mace_run.cc:291] Total init latency: 52.217 ms
I mace/tools/validation/mace_run.cc:331] Warm up run
I mace/tools/validation/mace_run.cc:363] 1st warm up run latency: 271.112 ms
I mace/tools/validation/mace_run.cc:370] Run model
I mace/tools/validation/mace_run.cc:414] Average latency: 233.17 ms
I mace/tools/validation/mace_run.cc:437] Write output file /tmp/data/mace_run/model_out_mbox_loc with size 7668 done.
I mace/tools/validation/mace_run.cc:437] Write output file /tmp/data/mace_run/model_out_mbox_conf_flatten with size 40257 done.
I mace/tools/validation/mace_run.cc:437] Write output file /tmp/data/mace_run/model_out_mbox_priorbox with size 15336 done.
I mace/libmace/mace.cc:564] Destroying MaceEngine
========================================
            init      warmup     run_avg
========================================
time      52.217     271.112     233.170
Running finished!
```


```
* Run 'ssd_mobilenet_v1' with round=1, restart_round=1, tuning=False, out_of_range_check=False, omp_num_threads=(-1,), cpu_affinity_policy=(1,), gpu_perf_hint=(3,), gpu_priority_hint=(3,)
Push builds/ssd-mobilenet-v1/_tmp/ssd_mobilenet_v1/f54c48d7f3efd2557cf6357f96c7916c/RockchipRK3399FireflyBoard_RK3399/arm64/model_input_data to /tmp/data/mace_run
Push builds/ssd-mobilenet-v1/model/ssd_mobilenet_v1.data to /tmp/data/mace_run
Push third_party/nnlib/libhexagon_controller.so to /tmp/data/mace_run
Push builds/ssd-mobilenet-v1/model/ssd_mobilenet_v1.pb to /tmp/data/mace_run/ssd_mobilenet_v1.pb
Push builds/ssd-mobilenet-v1/_tmp/arm64/mace_run_static to /tmp/data/mace_run
Push /tmp/cmd_file-ssd_mobilenet_v1-1559272510.88 to /tmp/data/mace_run/cmd_file-ssd_mobilenet_v1-1559272510.88
I mace/tools/validation/mace_run.cc:450] model name: ssd_mobilenet_v1
I mace/tools/validation/mace_run.cc:451] mace version: v0.10.0-30-g858dda5-20190531
I mace/tools/validation/mace_run.cc:452] input node: data
I mace/tools/validation/mace_run.cc:453] input shape: 1,300,300,3
I mace/tools/validation/mace_run.cc:454] output node: mbox_loc,mbox_conf_flatten,mbox_priorbox
I mace/tools/validation/mace_run.cc:455] output shape: 1,1,1,7668:1,40257,1:1,2,7668
I mace/tools/validation/mace_run.cc:456] input_file: /tmp/data/mace_run/model_input
I mace/tools/validation/mace_run.cc:457] output_file: /tmp/data/mace_run/model_out
I mace/tools/validation/mace_run.cc:458] model_data_file: /tmp/data/mace_run/ssd_mobilenet_v1.data
I mace/tools/validation/mace_run.cc:459] model_file: /tmp/data/mace_run/ssd_mobilenet_v1.pb
I mace/tools/validation/mace_run.cc:460] device: GPU
I mace/tools/validation/mace_run.cc:461] round: 1
I mace/tools/validation/mace_run.cc:462] restart_round: 1
I mace/tools/validation/mace_run.cc:463] gpu_perf_hint: 3
I mace/tools/validation/mace_run.cc:464] gpu_priority_hint: 3
I mace/tools/validation/mace_run.cc:465] omp_num_threads: -1
I mace/tools/validation/mace_run.cc:466] cpu_affinity_policy: 1
I mace/tools/validation/mace_run.cc:489] restart round 0
I mace/libmace/mace.cc:785] Create MaceEngine from model graph proto and weights data
I mace/libmace/mace.cc:432] Creating MaceEngine, MACE version: v0.10.0-30-g858dda5-20190531
I mace/libmace/mace.cc:464] Initializing MaceEngine
I mace/tools/validation/mace_run.cc:291] Total init latency: 898.942 ms
I mace/tools/validation/mace_run.cc:331] Warm up run
I mace/tools/validation/mace_run.cc:363] 1st warm up run latency: 1149.58 ms
I mace/tools/validation/mace_run.cc:370] Run model
I mace/tools/validation/mace_run.cc:414] Average latency: 319.366 ms
I mace/tools/validation/mace_run.cc:437] Write output file /tmp/data/mace_run/model_out_mbox_loc with size 7668 done.
I mace/tools/validation/mace_run.cc:437] Write output file /tmp/data/mace_run/model_out_mbox_conf_flatten with size 40257 done.
I mace/tools/validation/mace_run.cc:437] Write output file /tmp/data/mace_run/model_out_mbox_priorbox with size 15336 done.
I mace/libmace/mace.cc:564] Destroying MaceEngine
========================================
            init      warmup     run_avg
========================================
time     898.942    1149.584     319.366
Running finished!
```


## 1.模型转换
- [caffe版模型地址 mobilenetv1+ssd](https://github.com/chuanqi305/MobileNet-SSD)
- 在主机host上进入~/mace
- python tools/converter.py convert --config=/home/xuweixiang/mace/xwx_for_boards/ssd-mobilenet-v1_caffe.yml
- [yml文件参考](https://github.com/XiaoMi/mace-models/blob/master/ssd-mobilenet-v1/ssd-mobilenet-v1_caffe.yml)
- 在`/mace/build/ssd-mobilenet-v1/model`里模型文件和参数文件ssd_mobilenet_v1.pb ssd_mobilenet_v1.data


## 2.在rk3399测试间
- 注意：**代码只是在测试间**，要获得检测框只需要改改mace_net.cpp里的output。
- 可以得到的是mbox_loc，mbox_conf_flatten，mbox_priorbox；而不是最终的检测框，因为“In order to facilitate model optimization, we use the node "mbox_loc", "mbox_conf_flatten", "mbox_priorbox" as output. For the detection output layer, you can refer to detection_output.cc.”。[detection_output.cc代码在](https://github.com/XiaoMi/mace/blob/v0.10.0/mace/utils/detection_output.cc)
- 以下方式运行
```
cd build
cmake .
make
./mace_on_boards
```
- 关于mace_net.cpp的一些说明<br>
```
  //set CPU config
  int FLAGS_omp_num_threads = -1;
  int FLAGS_cpu_affinity_policy = 1;
  ...
  ...
  ...
    //set GPU config
  if(FLAGS_device == "GPU"){
    std::cout << "Beigin to set gpu config.\n";
    int FLAGS_gpu_perf_hint = 3;
    int FLAGS_gpu_priority_hint = 3;
    config_.SetGPUHints(
        static_cast<GPUPerfHint>(FLAGS_gpu_perf_hint),
        static_cast<GPUPriorityHint>(FLAGS_gpu_priority_hint));
```
<br>上面是对CPU和GPU模式的一些参数配置,MACE官方并没有给出这些参数的说明文档，如果想参考请见[MACE源码mace/examples/cli/example.cc](https://github.com/XiaoMi/mace/blob/master/examples/cli/example.cc)
