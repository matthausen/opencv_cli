This is a command line tool CLI which uses the openCV library to process images and video frames.
It supports resizing, frame capturing, document scanning and face detection.

The project uses CMake.


### Usage
```
./opencli --<command> [optional_file_path] [optional_resize_options]
```
### Examples

Print commands
```
./opencli --help
```
Resize image
```
./opencli --resize path_to_file.png 0.5 0.5
```