#include "linklist.h"

//创建链表
struct List*Create_linklist()
{
	struct List*list=(struct List*)malloc(sizeof(*list));
	list->first=NULL;
	list->last=NULL;
	return list;
}

//读文件及目录
struct List*search_dir(struct List*list,char *pathname)
{
	DIR*drip=opendir(pathname);
	if(drip==NULL)
	{
		perror("opendir error:");
	}
	struct dirent*dirent=NULL;
	while(dirent=readdir(drip))
	{
		if(strcmp(dirent->d_name,".")==0||strcmp(dirent->d_name,"..")==0)
		{
			continue;
		}
		char buf[128];
		sprintf(buf,"%s/%s",pathname,dirent->d_name);
		char *pr=buf;
		struct stat st;
		stat(buf,&st);
		if(S_ISREG(st.st_mode))
		{
			if(strcmp(pr+strlen(buf)-4,".mp3")==0)
			{
				add_a_node(list,buf);
			}
		}
		else if(S_ISDIR(st.st_mode))
		{
			search_dir(list,buf);
		}
	}
	return list;
	closedir(drip);
}

//插入链表
struct List*add_a_node(struct List*h,char *buf)
{
	struct inode*pnew=(struct inode*)malloc(sizeof(*pnew));
	strcpy(pnew->data,buf);
	if(h->first==NULL)
	{
		h->first=pnew;
		h->last=pnew;
	}
	else
	{
		h->last->next=pnew;
		pnew->prev=h->last;
		h->last=pnew;
	}
	return h;
}