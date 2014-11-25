Oscilloscope_analyzer
=====================
Arduino + Analog Shield Spectrum analyzer unsing oscilloscope

This Arduino sketch uses the Digilent Analog Shield and the Open Music Labs FHT library. 
It takes an input on A0 of the shield, produces a 128 bin FFT and returns the spectrum of the input signal on D0, as a pulse train. 
By setting your oscilloscope to trigger on the +5V pulse at the start of each frame, it will capture the plot as it passes by, 
using the scope as a 1-axis display. The scope input time base should be set to 0.5ms / div, as each frame (128 bins) is 5ms long.
Voltage should be ~1V/div to get a reasonable scale, and the vertical offset will be significant. If you see nothing, it is likely 
because your vertical offset or trigger is set incorrectly.
