#include<stdio.h>
#include<stdlib.h>
#define MS 100


int main(int argc, char *argv[])
{
  void READ_FILE(char * , int [MS][MS], int *, int *, int *);
  void DISPLAY(int [MS][MS], int );
  void DFS_p(int [MS][MS], int , int , int , int, int *);
  void PUSH(int , int [], int [],  int * , int ,  int );
  void POP(int , int [], int [], int *, int *, int *);
        
  int A[MS][MS], N, typ, vs, inf, cost, ch;
  char str[20], *FName;
    
  inf = 1;
// if someone fails to give arguments in command line...|||    
  if(argc < 2)
  {
    printf("\nEnter a File Name to open: ");
// read filename in run time...|||
    scanf("%s", str); 
    printf("\nEntered File Name is: %s\n\n", str);
    FName = str;
  }
  else
  {
    FName = argv[1];
  }
          
// READ_FILE() function calling...|||
  READ_FILE(FName, A, &N, &typ, &inf);
  if(N == 0)
  {
    return 0;
  }

  printf("\nNumber of vertex in the given graph: %d", N); 

// typ = 0, indicates unweighted undirected graph          
  if(typ == 0)
  {
    printf("\nType of the given graph is unweighted undirected graph\n");
  }

// typ = 1, indicates weighted undirected graph
  else if(typ == 1)
  {
    printf("\nType of the given graph is weighted undirected graph\n");
  }
    
// typ = 2, indicates unweighted directed graph
  else if(typ == 2)
  {
    printf("\nType of the given graph is unweighted directed graph\n");
  }

// typ = 3, indicates weighted directed grapg
  else
  {
    printf("\nType of the given graph is weighted directed graph\n");
  }
        
// DISPLAY() function calling...|||
  DISPLAY(A, N);
      
  printf("\nEnter the source vertex: ");
  scanf("%d", &vs);

  cost = 0;
      
//BFS_p() function calling...||
  DFS_p(A, N, vs, typ, inf, &cost);       
    
  if(typ == 1 || typ == 3)
  {
    printf("\nCost of the traversal: %d\n\n", cost);
  }   
    
  printf("If You Wants to Enter Another Graph, Press '1', to Exit, Press '0'\n");
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

//Display function of a matrix...|||
void DISPLAY(int A[MS][MS], int N)
{
  int i, j;
    
  printf("The given Augmented Matrix is:\n");
  printf("   ");
  for(i=1; i<=N; i++)
  {
// display column lables
    printf("%3d", i);
  }
  printf("\n");
    
  for(i=1; i<=N; i++)
  {
//display row lable
    printf("%3d", i);
    for(j=1; j<=N; j++)
    {
// display value of a particular position
      printf("%3d", A[i][j]);
    }
    printf("\n");
  }        
  return;
}

// File read function...|||
void READ_FILE(char * FName, int A[MS][MS], int *N, int *typ, int *inf)
{
  int ch, i, j, v, u, w;
  FILE * ptr;
  char str[20];
    
// file open in read mode...||    
  ptr=fopen(FName, "r");

// if failed to open file...|||  
  if(ptr == NULL)
  {
    puts("ERROR!! FAILED TO OPEN THE FILE");

    printf("\nIf You Wants to Enter the Augmented Matrix Manually, Press '1', if You Wants to Enter Another Graph, Press '0', To Exit Press Any Number rather '1' & '0': ");
        
    scanf("%d", &ch);
        
    if(ch == 1)
    {
      puts("\nEnter Augmented Matrix Manually~~");

// read number of vertex from keyboard into 'N' veriable...|||            
      printf("Enter number of vertex: ");
      scanf("%d", N);

/*
'typ' holds a value indicating type of the given graph. 
we mapped unweighted undirected graph, weghted undirected graph, unweighted direct graph, 
weighted directed graph in to 0, 1, 2, 3 respectively
*/            
      printf("Enter Type of the Graph: ");
      scanf("%d", typ);
            
      printf("NOTE: For weighted graph enter 0 for no adjacency of any vertex.\nEnter value of the augmented matrix~~\n");
            
      for(i=1; i<=(*N); i++)
      {
        for(j=1; j<=(*N); j++)
        {
          printf("A[%d][%d]: ", i, j);
          scanf("%d", &A[i][j]);
          (*inf) += A[i][j];
        }
      }
    }
    else if(ch == 0)
    {
      printf("\nEnter a File Name to open: ");
      scanf("%s", str); 
      printf("\nEntered File Name is: %s\n\n", str);
      FName = str;
      (*inf) = 1;
            
// READ_FILE() function calling...|||
      READ_FILE(FName, A, N, typ, inf);
    }
    else
    {
// on exit return number of vertex is zero... that helps to call DFS function
      (*N) = 0;
      puts("Session Exipre");
      return;
    }                
  }

// if file open successfully...|||
  else
  {
    puts("FILE OPEN SUCCESSFULLY");

// read number of vertex from file into 'N' veriable...|||
    fscanf(ptr, "%d", N);
    printf("Number of vertx: %d\n", *N);
        
// intializing '0' in all the elements...|||
    for(i=1; i<=(*N); i++) 
    {
      for(j=1; j<=(*N); j++)
      {
        A[i][j]=0;
      }
    }
/*
'typ' holds a value indicating type of the given graph. 
we mapped unweighted undirected graph, weghted undirected graph, unweighted direct graph, 
weighted directed graph in to 0, 1, 2, 3 respectively
*/
        
    fscanf(ptr, "%d", typ);
    
// untill file ends loop continue
    while(!feof(ptr))
    {
// read one edge from file into 'v' variable
      fscanf(ptr, "%d", &v);

// read 2nd edge from file into 'u' variable           
      fscanf(ptr, "%d", &u);

// for weighted graph read weight from file into 'w'...||        
      if((*typ) == 1 || (*typ) == 3)
      {
        fscanf(ptr, "%d", &w);
        *inf += w;
      } 

// Intializing end vertices by '1' for unweighted undirected graph...|||
      if((*typ) == 0)
      {
        A[v][u]=1;
        A[u][v]=1;
      }

// Intializing end vertices by 'w'(weight of the edge) for weighted undirected graph...||| 
      else if((*typ) == 1)
      {
        A[v][u]=w;
        A[u][v]=w;
      }

// Intializing end vertices by '1' for unweighted directed graph...|||       
      else if((*typ) == 2)
      {
        A[v][u]=1;
      }

// Intializing end vertices by 'w'(weight of the edge) for weighted directed graph...|||      
      else
      {
        A[v][u]=w;
      }
    } // while(!feof(ptr))[End of the file]
    fclose(ptr); //file close
  }

// for weighted graph intializing infinity for indicating no edge between two vertex...|||
  if(*typ == 1 || *typ == 3)
  {
    for(i=1; i<=(*N); i++)
    {
      for(j=1; j<=(*N); j++)
      {
        if(i != j)
        {
          if(A[i][j] == 0)
          {
            A[i][j] = (*inf);
          } // end of if((*(A+(i*N)+j)) == 0)
        } // end of if(i != j)
      } // end of for(j=1; j<=N; j++)
    } // for(i=1; i<=N; i++)
  } // if(typ == 1 || typ == 3)
  return;
} // end of READ_FILE() function

//DFS function
void DFS_p(int A[MS][MS], int N, int vs, int typ, int inf, int *cost)
{
  void PUSH(int , int [], int [],  int * , int ,  int );
  void POP(int , int [], int [], int *, int *, int *);
    
  int i, St[N], x, y, top, Svs[N], Sva[N];
    
  x = vs;
  y = -1;

    
// intialize '0' for all vertex...|||
  i=1;
  while(i<=N)
  {
    St[i]=0;
    i+=1;
  }

// intially top= -1, that indicates stack is empty    
  top = -1;
    
// PUSH function calling...||
  PUSH(N, Svs, Sva, &top, x, y);
    
// make status '1' for vertex 'vs'
  St[vs] = 1;
    
  while(top != -1)
  {
//POP function calling
    POP(N, Svs, Sva, &top, &x, &y);
        
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
// PUSH function insert
            PUSH(N, Svs, Sva, &top, i, x);
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
// PUSH function calling
              PUSH(N, Svs, Sva, &top, i, x);
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

//push function...||
void PUSH(int N, int Svs[N], int Sva[N],  int * top, int x,  int y)
{
  if((*top) == N)
  {
    return;
  }
        
  (*top) += 1;
        
  Svs[(*top)] = x;
  Sva[(*top)] = y;
    
  return;
}

//pop function...||
void POP(int N, int Svs[N], int Sva[N], int *top, int *x, int *y)
{
  if((*top) == -1)
  {
    return;
  }
    
  *x = Svs[(*top)];
  *y = Sva[(*top)];
    
  *top -= 1;
    
  return;
}