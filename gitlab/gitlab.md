������ʹ�õ���centos 7 64bit,���Թ�centos 6Ҳ�ǿ��Ե�!
1. ��װ�������
yum -y install policycoreutils openssh-server openssh-clients postfix
2.����postfix������������������postfix֧��gitlab���Ź���
systemctl enable postfix && systemctl start postfix
3.����gitlab��װ����Ȼ��װ
centos 6ϵͳ�����ص�ַ:https://mirrors.tuna.tsinghua.edu.cn/gitlab-ce/yum/el6
centos 7ϵͳ�����ص�ַ:https://mirrors.tuna.tsinghua.edu.cn/gitlab-ce/yum/el7
�ҵ���centos7,��������https://mirrors.tuna.tsinghua.edu.cn/gitlab-ce/yum/el7�����˸�gitlab8.0.0�汾,��������һ���Ƚ��µİ汾,������ѡ��һ���ȽϾɵİ汾������ʵ��
����rpm������װ:
wget https://mirrors.tuna.tsinghua.edu.cn/gitlab-ce/yum/el7/gitlab-ce-8.0.0-ce.0.el7.x86_64.rpm
rpm -i gitlab-ce-8.0.0-ce.0.el7.x86_64.rpm
4.�޸�gitlab�����ļ�ָ��������ip���Զ���˿ڣ�
vim  /etc/gitlab/gitlab.rb
external_url 'http;//xxx.xxx.xxx.xxx'

:ע���������õĶ˿ڲ��ܱ�ռ�ã�Ĭ����8080�˿ڣ����8080�Ѿ�ʹ�ã����Զ��������˿ڣ����ڷ���ǽ���ÿ������Ӧ�ö˿�

5.���ò�����GitLab
ִ�У�
gitlab-ctl reconfigure
gitlab-ctl restart


�廪��ѧ��Դ�������վ:  https://mirrors.tuna.tsinghua.edu.cn/


Command line instructions
Git global setup

git config --global user.name "songweifly"
git config --global user.email "songweifly@126.com"

һ��Create a new repository

git clone http://132.147.253.210/songweifly/SwLiveBase.git
cd SwLiveBase
touch README.md
git add README.md
git commit -m "add README"
git push -u origin master

����Existing folder

cd existing_folder
git init
git remote add origin http://132.147.253.210/songweifly/SwLiveBase.git
git add .
git commit -m "Initial commit"
git push -u origin master

����Existing Git repository

cd existing_repo
git remote add origin http://132.147.253.210/songweifly/SwLiveBase.git
git push -u origin --all
git push -u origin --tags


