default: build

.PHONY: clean
clean:
	rm -rf ./_build 
 
prepare: ./_build model_download

./_build: 
	mkdir -p _build && cd _build && cmake . -S ../

model_download:	./model/face_recognition_sface_2021dec.onnx ./model/LICENSE

./model/face_recognition_sface_2021dec.onnx:
	mkdir -p model && \
	wget https://github.com/opencv/opencv_zoo/raw/main/models/face_recognition_sface/face_recognition_sface_2021dec.onnx -O ./model/face_recognition_sface_2021dec.onnx

./model/LICENSE:
	wget https://github.com/opencv/opencv_zoo/raw/main/models/face_recognition_sface/LICENSE -O ./model/LICENSE

build: prepare
	cmake --build ./_build/

.PHONY: sample
sample: build
	./_build/recbot_sampler

.PHONY: train
train: build
	./_build/recbot_trainer

.PHONY: recon
recon: build
	./_build/recbot_recon

