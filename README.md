# ROS-Neuro Flattop window

This ROS-Neuro filter plugin applies a Flattop window to the provided data.

## Algorithm:
The filter applies the Flattop window to the data. The Flattop window is implemented as follows:
```cpp
    const double A0 = 0.215578950;
    const double A1 = 0.416631580;
    const double A2 = 0.277263158;
    const double A3 = 0.083578947;
    const double A4 = 0.006947368;		
    
    int nsamples;
    for(auto i = 0; i<nsamples; i++)
      window.at(i) = A0 - A1*cos((2.0 * M_PI * i)/(nsamples-1)) + A2*cos((4.0 * M_PI * i)/(nsamples-1)) - A3*cos((6.0 * M_PI * i)/(nsamples-1)) + A4*cos((8.0 * M_PI * i)/(nsamples-1));
```
The provided window filters do not required mandatory parameters but the name and the type.
An example of the YAML configuration:
```
FlattopCfgTest:
  name: flattop
  type: FlattopWindowFloat
```
