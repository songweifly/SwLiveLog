我这里使用的是centos 7 64bit,我试过centos 6也是可以的!
1. 安装依赖软件
yum -y install policycoreutils openssh-server openssh-clients postfix
2.设置postfix开机自启，并启动，postfix支持gitlab发信功能
systemctl enable postfix && systemctl start postfix
3.下载gitlab安装包，然后安装
centos 6系统的下载地址:https://mirrors.tuna.tsinghua.edu.cn/gitlab-ce/yum/el6
centos 7系统的下载地址:https://mirrors.tuna.tsinghua.edu.cn/gitlab-ce/yum/el7
我的是centos7,所以我在https://mirrors.tuna.tsinghua.edu.cn/gitlab-ce/yum/el7中找了个gitlab8.0.0版本,建议下载一个比较新的版本,我这里选了一个比较旧的版本仅仅是实验
下载rpm包并安装:
wget https://mirrors.tuna.tsinghua.edu.cn/gitlab-ce/yum/el7/gitlab-ce-8.0.0-ce.0.el7.x86_64.rpm
rpm -i gitlab-ce-8.0.0-ce.0.el7.x86_64.rpm
4.修改gitlab配置文件指定服务器ip和自定义端口：
vim  /etc/gitlab/gitlab.rb
external_url 'http;//xxx.xxx.xxx.xxx'

:注意这里设置的端口不能被占用，默认是8080端口，如果8080已经使用，请自定义其它端口，并在防火墙设置开放相对应得端口

5.重置并启动GitLab
执行：
gitlab-ctl reconfigure
gitlab-ctl restart


清华大学开源软件镜像站:  https://mirrors.tuna.tsinghua.edu.cn/


Command line instructions
Git global setup

git config --global user.name "songweifly"
git config --global user.email "songweifly@126.com"

一、Create a new repository

git clone http://132.147.253.210/songweifly/SwLiveBase.git
cd SwLiveBase
touch README.md
git add README.md
git commit -m "add README"
git push -u origin master

二、Existing folder

cd existing_folder
git init
git remote add origin http://132.147.253.210/songweifly/SwLiveBase.git
git add .
git commit -m "Initial commit"
git push -u origin master

三、Existing Git repository

cd existing_repo
git remote add origin http://132.147.253.210/songweifly/SwLiveBase.git
git push -u origin --all
git push -u origin --tags


