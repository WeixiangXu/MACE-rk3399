void SoftmaxOp::Compute(const vector<Blob*>& in,
		const vector<Blob*>& out){
  N_ = in[0]->num();
  C_ = in[0]->channels();
  H_ = in[0]->height();
  W_ = in[0]->width();

  const float* input_ptr = in[0]->data<float>();
  float* output_ptr = out[0]->mutable_data<float>();

  //step1: calcute for scale, which size is [C,1]
  for(int c = 0; c < C_; ++c){
    float scale_tmp = 0;
    for(int n = 0; n < N_; ++n){
      for(int h = 0; h < H_; ++h){
        for(int w = 0; w < W_; ++w){
          scale_tmp += exp(input_at(input_ptr, n, c, h, w) );
        }
      }
    }

    scale_.push_back(scale_tmp);
  }

  //step2:
  int out_index;
  for(int c = 0; c < C_; ++c){
    for(int n = 0; n < N_; ++n){
      for(int h = 0; h < H_; ++h){
        for(int w = 0; w < W_; ++w){
          out_index = n*C_*H_*W_ + c*H_*W_ + h*W_+w;
          output_ptr[out_index] = exp(input_at(input_ptr, n, c, h, w)) / scale_[c];

	  if (output_ptr[out_index] > 1e10){
	  std::cout << "output_ptr[out_index]: " << output_ptr[out_index]<<std::endl;
	  std::cout << "exp(input_at(input_ptr, n, c, h, w)): " << exp(input_at(input_ptr, n, c, h, w)) << std::endl; 
	  std::cout << "scale_[c]: " << scale_[c] << std::endl;}
        }
      }
    }    
  }

}
