#include"lcd.h"
#include"linklist.h"
#include"bmp.h"
#include <sys/wait.h>
int Input(int *x,int *y)
{
	int dev_fd=open("/dev/input/event0",O_RDONLY);
	if(dev_fd==-1)
	{
		perror("dev error:");
		return -1;
	}
	struct input_event event;
	int div;

	while(1)
	{
		int r = read(dev_fd,&event,sizeof(struct input_event));
		if(r != sizeof(struct input_event))
		{
			continue;
		}
		if(event.type == EV_ABS && event.code == ABS_X)
		{
			*x = event.value;
			printf("%d\n",*x);
		}
		
		if(event.type == EV_ABS && event.code == ABS_Y)
		{
			*y = event.value;
			printf("%d\n",*y);
		}
		
		if(event.type == EV_KEY&& event.value == 0)
		{
			break;
		}
	}
	//返回手离开的点与手触碰的点的位置值得差值
	return 0;
	close(dev_fd);
}


int main(int argc,char **argv)
{
	Init_lcd();
	
	//创建链表
	struct List*list=Create_linklist();
	
	//读取目录
	int x,y;
	list=search_dir(list,argv[1]);
	struct inode*p=list->first;
	if(0 == strcmp(argv[2]+strlen(argv[2])-4,".bmp"))
	{
		bmp_display(argv[2]);
	}
	pid_t pid;
	while(1)
	{
		pid = fork();
		if(-1 == pid)
		{
			printf("fork error:");
			exit(1);
		}
		else if(0 == pid)
		{
			
			printf("%s\n",p->data);
			execl("/usr/bin/mplayer","mplayer",p->data,NULL);
		}
		else
		{
			int i = 1;
			while(1)
			{
				Input(&x,&y);
				//初始化lcd
				if(x>470&&x<520&&y>270&&y<300)				//暂停及恢复
				{
					if(1 == i%2)
					{
						system("killall -STOP mplayer");
						i++;
					}
					else
					{
						system("killall -CONT mplayer");
						i++;
					}
				}
				
				if(x>400&&x<450&&y>270&&y<300)				//上一首
				{
					p=p->prev;
					if(p==NULL)
					{
						p=list->last;
					}
					system("killall -9 mplayer");
					
					wait(NULL);
					break;
				}
				
				if(x>540&&x<590&&y>270&&y<300)				//下一首
				{
					p=p->next;
					if(p==NULL)
					{
						p=list->first;
					}
					system("killall -9 mplayer");
					
					wait(NULL);
					break;
				}
				if(x>750&&x<800&&y>0&&y<35)						//退出
				{
					system("killall -9 mplayer");
					exit(0);
				}
			}	
		}
	}
	close_lcd();
}