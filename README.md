# RECBOT: Experiments on Face detection and recognition 

Uses HAR cascades for fast good-enough face detection.
Uses [SFace](https://github.com/opencv/opencv_zoo/tree/main/models/face_recognition_sface) for face recognition via cosine similarity against model computed features of samples.

Remember:
- Face Detection: is there a face in the image?
- Face Recognition: whose face is in the image

## Dependencies
- Install/Compile libopencv-dev and opencv-data
- Install cmake, make, and g++

Will use `-march=native` in order to enable SSE, AVX, et al. where possible.

## Using
- `make prepare` will prepare cmake directories and download model and it's LICENSE.
- `make build` will build everything
- `make sample` will run the sampler to capture 10 samples of a face using the computer camera and crop it to the bounding box found by the face detector.
- `make recon` will run the recognizer and output "PASS" or "FAIL", with exist codes 0 or -1 respectively.

Binaries can be found on `_build/`.

## Notes:

### Choosing the camera 
You can change the camera by changing the index (0) on:
`#define CAMERA_INDEX 0`
in both `recbot_recon.cpp` and `recbot_samples.cpp`. Use `ls /dev/video*` to list, and note that not all devices are actual cameras.

### Simple Detection Example
Under `./examples/` you can check a simple face detection example using HAR Cascades. 

## Troubleshooting:
If vscode intellisense is not working add "/usr/include/**" or equivalent to `includePath` in the C/C++ properties (`c_cpp_properties.json`).


## TODO:
- Command line argument parsing
- Make this work with PAM for authentication
- Ensure memory is not leaking, because right now this runs as a one shot POC and I didn't care.
