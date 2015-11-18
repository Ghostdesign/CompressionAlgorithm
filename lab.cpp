#include <errno.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;
#define CLE 226

int main()
{
	struct msqid_ds buf ;
	int msqid ;

	// récupération de l'identificateur de la file de messages de clé 222 
	if (( msqid = msgget(CLE,0))  == -1 ) 
		{
		perror ("Erreur msgget()") ;
		exit(1) ;
		}
	//on récupère dans la structure buf les paramètres de al file 
	if (msgctl(msqid,IPC_STAT,&buf) == -1)
		{
		perror("Erreur msgctl()") ;
		exit(1) ;
		}
	else
		{
		cout <<"id de la file de messages :" <<  msqid <<endl;
		cout <<"id du propriétaire : " << buf.msg_perm.uid<<endl ;
                       cout << "id du groupe du propriétaire : "<< buf.msg_perm.gid<<endl ;
		cout <<"droits d'accès :" << buf.msg_perm.mode<<endl ;
                       cout <<"nb courant d'octets dans la file :"<< buf.msg_cbytes<<endl;
		cout <<"nb de messages dans la file :"<<  buf.msg_qnum<<endl ;
                       cout <<"nb maximal d'octets de la file : "<< buf.msg_qbytes<<endl ;
		cout << "pid du dernier écrivain :"<< buf.msg_lspid<<endl ;
		cout <<"pid du dernier lecteur : "<< buf.msg_lrpid<<endl ;
      cout << "date de la dernière écriture :"<<ctime(&buf.msg_stime)<<endl;
		cout <<"date de la dernière lecture : "<< ctime(&buf.msg_rtime)<<endl;
      cout <<"date du dernier changement :"<< ctime(&buf.msg_ctime)<<endl;
		}
	return (0);
}