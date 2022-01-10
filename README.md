# LiveRGB
Change devices RGB based on display color using **[OpenRGB](https://github.com/CalcProgrammer1/OpenRGB)**
> It currently only runs on X11 window system, and tested only on 1080p displays

****

LiveRGB works by scanning pixels on the screen and getting the average color.
Note that it doesn't scan *all* pixels on the screen as that would take almost 10 minutes
which wouldn't make it very "Live".

You can change the quality variable to a value between 1 and 10.
Here is a chart of how long each quality setting takes.

> The results are tested using my **Amd 3200g**

| Quality | Time |
| ----------- | ----------- |
| 1 | 0m0.008s |
| 2 | 0m0.136s |
| 3 | 0m0.673s |
| 4 | 0m2.512s |
| 5 | 0m6.637s |
| 6 | 0m15.870s |
| 7 | 0m29.114s |
| 8 | 1m24.416s |
| 9 | 3m22.458s |
| 10 | 13m3.580s |

## Build
`git clone https://github.com/thesusian/LiveRGB.git`

`cd LiveRGB && make`

`./LiveRGB`
