src <== 放的是源代码
binary <== 放的是可以直接在金字塔中使用的dll

关于破冰号在金字塔中的使用说明（所有文件都放在binary目录下）。
1. 把root目录下的ibt_log4cplus.properties,libibt_client_ex.dll,msvcp100.dll,msvcr100.dll复制到金字塔安装的根目录下（即启动目录Weisoft Stock）
2. 把FmlDLL目录下的ibt_jzt.dll,ibt_jzt_zk.dll复制到启动目录Weisoft Stock下的FmlDLL目录里面
3. 启动金字塔，把demo目录下的ibt_demo.fla，ibt_demo2.fla导入到金字塔中。

特别说明：
1. ibt_demo.fla 用在序列K线中，调用的dll是ibt_jzt.dll
2. ibt_demo2.fla 用在逐K线中，调用的dll是ibt_jzt_zk.dll
