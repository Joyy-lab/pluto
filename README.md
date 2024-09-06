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
`jupyter notebook --config /datahome/home**/your/username**/.jupyter/jupyter_notebook_config.py --allow-root`

