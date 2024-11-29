# pluto
Modified PLUTO code

## pload
New pload file for python>=3.8

## 运行结果输出到文件
`./pluto > pluto.log &`

## jupyter
服务器运行jupyter notebook
1. 将jupyter下的`jupyter_notebook_config.py`放到家目录的.jupyter目录下，并相应做一些修改：
```
c.NotebookApp.port = 8888 #改一个其他端口
c.NotebookApp.notebook_dir = "/data/home/your/username" #改成自己的家目录或者其他存在的目录
```
2. 在服务器终端执行
```
jupyter notebook --config /data/home/your/username/.jupyter/jupyter_notebook_config.py --allow-root
```
## 202410计划
1. 高分辨率模拟（Nr~1000）
2. M81\*参数，参考Shi et al. 2024 (r0\~0.1pc, r1\~30pc, t\~20000yr)
3. 尝试引入辐射冷却（tabulated cooling, 参考pluto user guide）

## 20241020计划
1. 介质密度1E4,考虑和不考虑冷却的区别
2. 考虑团块化的核周介质，随机的高密度团块或者lognormal的密度分布

## 20241027计划
1. 高密度介质限制在1pc以内，1pc外设置0.1mp/cm3的密度。使高密度介质质量在1000太阳质量左右。
2. 考察团块化的介质的设置，参考Ward et al. 2024以及Banda-Barragan et al (doi: 10.1093/mnras/staa2904). 2020.

## 20241119计划
1. 考虑与不考虑团块的模拟
2. 计算X射线光度，计算辐射平均的温度和速度

## 20241129计划
1. g_minCoolingTemp设到50000 K。介质和团块的密度考虑1E4和1E5左右，团块质量比可以约为1/10。
2. 添加对clump的tracer。definitions.h中将NTRACER改至2，在init.c中添加对TRC+1的定义。
3. 考察使用[pyfc](https://pypi.org/project/pyFC/)生成clumpy的密度场，参考[Ward et al. 2024](https://arxiv.org/abs/2407.17593)以及[Banda-Barragan et al](https://ui.adsabs.harvard.edu/abs/2020MNRAS.499.2173B)
