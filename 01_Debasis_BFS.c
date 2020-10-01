#include<stdio.h>
#include<stdlib.h>
#define MS 100

int main(int argc, char *argv[])
{
    void BFS_p(int [MS][MS], int , int , int , int, int *);
    void q_insert(int , int [], int [], int * , int *, int , int );
    void q_delete(int , int [], int [], int *, int *, int *, int *);
        
    int A[MS][MS], N, i, v, u, w, typ, j, vs, inf, cost, ch;
    FILE *ptr;
    char str[20], *FName;
    
    inf = 1;
    cost = 0;
    
    if(argc < 2)
    {
        printf("\nEnter a File Name to open: ");
        scanf("%s", str); 
        printf("\nEntered File Name is: %s\n\n", str);
        FName = str;
    }
    else
    {
        FName = argv[1];
    }
    
//file open in read mode...||    
    ptr=fopen(FName, "r");
    
    if(ptr == NULL)
    {
        puts("ERROR!! FAILED TO OPEN THE FILE");
        printf("\nIf You Wants to Enter the Augmented Matrix Manually, Press '1', if You Wants to Enter Another Graph, Press '0', To Exit Press Any Number rather '1' & '0': ");
        
        scanf("%d", &ch);
        
        if(ch == 1)
        {
            puts("\nEnter Augmented Matrix Manually~~");
            
            printf("Enter number of vertex: ");
            scanf("%d", &N);
            
            printf("Enter Type of the Graph: ");
            scanf("%d", &typ);
            printf("NOTE: For weighted graph enter 0 for no adjacency of any vertex.\nEnter value of the augmented matrix~~\n");
            
            for(i=1; i<=N; i++)
            {
                for(j=1; j<=N; j++)
                {
                    printf("A[%d][%d]: ", i, j);
                    scanf("%d", &A[i][j]);
                    inf += A[i][j];
                }
            }
        }
        else if(ch == 0)
        {
            main(argc, argv);
        }
        else
        {
            puts("Session Exipre");
            return 1;
        }
        
        
    }
    else
    {
        puts("FILE OPEN SUCCESSFULLY");

        fscanf(ptr, "%d", &N);
        printf("Number of vertx: %d\n", N);
        
        // intializing '0' in all the elements  
        for(i=1; i<=N; i++) 
        {
            for(j=1; j<=N; j++)
            {
                A[i][j]=0;
            }
        }
        fscanf(ptr, "%d", &typ);
                
        i=1;
    
//untill file ends loop continue
        while(!feof(ptr))
        {
            fscanf(ptr, "%d", &v);
            fscanf(ptr, "%d", &u);
        
            if(typ == 1 || typ == 3)
            {
                fscanf(ptr, "%d", &w);
                inf += w;
            } 
      
            if(typ == 0)
            {
                A[v][u]=1;
                A[u][v]=1;
            }
            else if(typ == 1)
            {
               A[v][u]=w;
               A[u][v]=w;
            }
        
            if(typ == 2)
            {
                A[v][u]=1;
            }
        
            if(typ == 3)
            {
                A[v][u]=w;
            }
        } // while(!feof(ptr))
        fclose(ptr);
    }
    
    if(typ == 1 || typ == 3)
    {
        for(i=1; i<=N; i++)
        {
            for(j=1; j<=N; j++)
            {
                if(i != j)
                {
                    if(A[i][j] == 0)
                    {
                        A[i][j] = inf;
                    } // end of if((*(A+(i*N)+j)) == 0)
                } // end of if(i != j)
            } // end of for(j=1; j<=N; j++)
        } // for(i=1; i<=N; i++)
    } // if(typ == 1 || typ == 3)
        
    if(typ == 0)
    {
        printf("\nType of the given graph is unweighted undirected graph\n");
    }
      
    if(typ == 1)
    {
        printf("\nType of the given graph is weighted undirected graph\n");
    }
    
    if(typ == 2)
    {
        printf("\nType of the given graph is unweighted directed graph\n");
    }
        
    if(typ == 3)
    {
        printf("\nType of the given graph is weighted directed graph\n");
    }
    
//Display the Augmented matrix...|| 
    printf("\nNumber of Vertex: %d", N); 
    printf("The given Augmented Matrix is:\n");
    printf("   ");
    for(i=1; i<=N; i++)
    {
        printf("%3d", i);
    }
    printf("\n");
    
    for(i=1; i<=N; i++)
    {
        printf("%3d", i);
        for(j=1; j<=N; j++)
        {
            printf("%3d", A[i][j]);
        }
        printf("\n");
    }
    
    printf("\nEnter the source vertex: ");
    scanf("%d", &vs);
    
//BFS function calling...||
    BFS_p(A, N, vs, typ, inf, &cost);       
    
    if(typ == 1 || typ == 3)
    {
       printf("\nCost of the traversal: %d\n", cost);
    }   
    
    printf("If You Wants to Check Another Graph, Press '1', to Exit, Press '0'\n");
    scanf("%d", &ch);
    if(ch == 1)
    {
        main(argc, argv);
    }
    else
    {
        return 1;
    }    
}

//BFS function
void BFS_p(int A[MS][MS], int N, int vs, int typ, int inf, int *cost)
{
    void q_insert(int , int [], int [], int * , int *, int , int );
    void q_delete(int , int [], int [], int * , int *, int *, int *);
    
    int i, St[N], x, y, front, rear, Qvs[N], Qva[N];
    
    x = vs;
    y = -1;

// allocate memory for St array        
//    St = (int *) malloc( N * sizeof(int) );
    
// intialize '0' for all elements in the array
    i=1;
    while(i<=N)
    {
        St[i]=0;
        i+=1;
    }
    
    front = -1;
    rear = -1;
    
// queue insert function calling...||
    q_insert(N, Qvs, Qva, &front, &rear, x, y);
    
// make status '1' for vertex 'vs'
    St[vs] = 1;
    
    while(front != -1)
    {
// queue delete function calling
        q_delete(N, Qvs, Qva, &front, &rear, &x, &y);
        
        printf("Traverse Vertex::%4d || Parent Vertex::%4d\n", x, y);
        
        i = 1;
        while(i <= N)
        {
            if(typ == 0 || typ == 2)
            {
                if(A[x][i] == 1)
                {
                    if(St[i] == 0)
                    {
// queue insert function insert
                        q_insert(N, Qvs, Qva, &front, &rear, i, x);
                        St[i] = 1;
                    } // end of if((*(St + i)) == 0)
                } // end of if(*(A +(x*N) + i) == 1)
            } //end of if(typ == 0 || typ == 2)
            
            if(typ == 1 || typ == 3)
            {
                if(A[x][i] != inf)
                {
                    if(A[x][i] != 0)
                    {
                        if(St[i] == 0)
                        {
// queue insert function calling
                            q_insert(N, Qvs, Qva, &front, &rear, i, x);
                            St[i] = 1;
                            *cost += A[x][i];
                        } // end of if((*(St + i)) == 0)
                    } // end of if(*(A +(x*N) + i) != 0)
                } // end of if(*(A +(x*N) + i) != inf)
            } // end of if(typ == 1 || typ == 3)
            i += 1;
        } // end of while(i <= N)
    } // end of while(front != NULL)
    return;
}

//queue insert function...||
void q_insert(int N, int Qvs[N], int Qva[N],  int * front, int * rear, int x,  int y)
{
//    Node * NN;
    
/* allocate memory for new node    
    NN = (Node *) malloc( 1 * sizeof(Node) );
    
    if(NN == NULL)
    {
        puts("ERROR!! FAILED TO ALLOCATE NEW NODE");
        return;
    }
    else
    {
        (NN -> dc) = x;
        (NN -> da) = y;
        (NN -> Next) = NULL;
    }
*/
    if((*rear) == N)
    {
        return;
    }
        
    if((*rear) == -1)
    {
        (*rear) += 1;
        
        Qvs[(*rear)] = x;
        Qva[(*rear)] = y;
        
        *front = *rear;
    }
    else
    {
        (*rear) += 1;
        
        Qvs[(*rear)] = x;
        Qva[(*rear)] = y;
    }
    return;
}

//Queue delete function...||
void q_delete(int N, int Qvs[N], int Qva[N], int * front, int *rear, int *x, int *y)
{
    
    if((*front) == -1)
    {
        return;
    }
    
    *x = Qvs[(*front)];
    *y = Qva[(*front)];
        
    if((*front)==(*rear))
    {
        (*front) = -1;
        (*rear) = -1;
    }
    else
    {
        (*front) += 1;
    }
    
    return;
}