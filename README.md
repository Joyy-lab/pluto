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

## 202420计划
1. 介质密度1E4,考虑和不考虑冷却的区别
2. 考虑团块化的核周介质，随机的高密度团块或者lognormal的密度分布
