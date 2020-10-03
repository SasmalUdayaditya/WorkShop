#include<stdio.h>
#include<stdlib.h>
#define MS 100


int main(int argc, char *argv[])
{
  void READ_FILE(char * , int [MS][MS], int *, int *, int *);
  void DISPLAY(int [MS][MS], int );
  void prims(int [MS][MS], int , int , int , int , int *, int [MS][MS]);
        
  int A[MS][MS], M[MS][MS], N, typ, vs, inf, cost, ch;
  char str[20], *FName;
    
  inf = 1;
// if someone fails to give filename in command line...|||    
  if(argc < 2)
  {
    printf("Enter a File Name to open: ");
// read filename in run time...|||
    scanf("%s", str); 
    printf("Entered File Name is: %s\n\n", str);
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

  printf("\n\nNumber of vertex in the given graph: %d", N); 

// typ = 0, indicates unweighted undirected graph          
  if(typ == 0)
  {
    printf("\n\nType of the given graph is unweighted undirected graph\n");
  }

// typ = 1, indicates weighted undirected graph
  else if(typ == 1)
  {
    printf("\n\nType of the given graph is weighted undirected graph\n");
  }
    
// typ = 2, indicates unweighted directed graph
  else if(typ == 2)
  {
    printf("\n\nType of the given graph is unweighted directed graph\n");
  }

// typ = 3, indicates weighted directed grapg
  else
  {
    printf("\n\nType of the given graph is weighted directed graph\n");
  }
        
// DISPLAY() function calling, Display the given graph...|||
  printf("The given graph is:\n");
  DISPLAY(A, N);
  
  printf("\nEnter the source vertex: ");
  scanf("%d", &vs);

  cost = 0;
      
//prims() function calling...||
  prims(A, N, vs, typ, inf, &cost, M);       

// DISPLAY() function calling, Minimum spannig tree display...|||
  printf("\nThe Minimum Spanning Tree is:\n");
  DISPLAY(M, N);
  
// for weighted graph display the cost of the traversal...|||    
  if(typ == 1 || typ == 3)
  {
    printf("\nCost of the traversal: %d\n\n", cost);
  }   
    
  printf("\nIf You Wants to Enter Another Graph, Press '1', to Exit, Press '0'\n");
  scanf("%d", &ch);
  if(ch == 1)
  {
    main(argc, argv);
  }
  else
  {
    puts("Session Expire");
  }
  return 0;
}

//Display function of a matrix...|||
void DISPLAY(int A[MS][MS], int N)
{
  int i, j;
    
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
      puts("\n\nEnter Augmented Matrix Manually~~");

// read number of vertex from keyboard into 'N' veriable...|||            
      printf("\nEnter number of vertex: ");
      scanf("%d", N);

/*
'typ' holds a value indicating type of the given graph. 
we mapped unweighted undirected graph, weghted undirected graph, unweighted direct graph, 
weighted directed graph in to 0, 1, 2, 3 respectively
*/            
      printf("Enter Type of the Graph: ");
      scanf("%d", typ);
            
      printf("\nNOTE: For weighted graph enter 0 for no adjacency of any vertex.\n\nEnter value of the augmented matrix~~\n");
            
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
// on exit return number of vertex is zero... that helps to call prims function
      (*N) = 0;
      puts("Session Exipre");
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
                            
//Prim's function
void prims(int A[MS][MS], int N, int vs, int typ, int inf, int *cost, int M[MS][MS])
{
  int i, j, St[MS], x, y, Nov, mc;
    
// intialize '0' for all elements in the matrix and status array
    
  for(i=1; i<=N; i++)
  {
    for(j=1; j<=N; j++)
    {
      M[i][j] = 0;
    }
    St[i] = 0;
  }
      
// make status '1' for vertex 'vs'
  St[vs] = 1;
  Nov = 1;
    
  while(Nov < N)
  {
    mc = inf;
    i = 1;
    while(i <= N)
    {
// if status of a vertex is '1' then continue with that vertex...|||
      if(St[i] == 1)
      {
        j = 1;
        while(j <= N)
        {
// if status of a verrex is '0', means that vertex is not traverse yet, and may be adjacency vertex of ith vertex...|||
          if(St[j] == 0)
          {
// if the graph type is unweighted then below if block will help to find MST...|||
            if(typ == 0 || typ == 2)
            {
// A[i][j] = 1, indicates that i & j connected, and last adjacency vertex will consider...|||
              if(A[i][j] == 1)
              {
                x = i;
                y = j;
              }
            }
// for weighted graph below else block will consider, and help to find the MST...|||           
            else
            {
// A[i][j] != inf, means i & j connect with a weight iff i != j
              if(A[i][j] != inf)
              {
                if(i != j)
                {
// mc > A[i][j], means that end vertices connected by i & j, have the less weight than mc, and the last adjacency vertex will consider, cause that end vertices have the minimum weight...|||
                  if(mc > A[i][j])
                  {
                    mc = A[i][j];
                    x = i;
                    y = j;
                  } //if(mc > A[i][j])
                } //if(i != j)
              } //if(A[i][j] != inf)          
            } // end of else
          } //if(St[j] == 0)
          j += 1; // update of while(j <= N)
        } //while(j <= N)
      } //if(St[i] == 1)
      i += 1; // update of while(i <= N)
    } //while(i <= N)
        
// for the undirected graph if block will consider and intialize those vertex whose have the minimum weight...|||
    if(typ == 0 || typ == 1)
    {
      M[x][y] = A[x][y];
      M[y][x] = A[x][y];
    }

// for the directed graph else block will consider and intialize those vertex whose have the minimum weight...|||        
    else
    {
      M[x][y] = A[x][y];
    }
// update cost w.r.t last traversed vertex...|||
    *cost += A[x][y];
// make the status '1' of last traversed vertex...|||
    St[y] = 1;
// update Nov...|||
    Nov += 1;
        
  } //while(Nov < N)

// for weighted graph initialize infinity to indicate no edge between any vertex of the Minimum spanning tree...||| 
  if(typ == 1 || typ == 3)
  {
    for(i=1; i<=N; i++)          
    {
      for(j=1; j<=N; j++)
      {
        if(i != j)
        {
          if(M[i][j] == 0)
          {
            M[i][j] = ((*cost) + 1);
          } // end of if(M[i][j] == 0)
        }  // ene of if(i != j)
      } // end of for(j=1; j<=N; j++)
    } // end of for(i=1; i<=N; i++)
  } // end of if(typ == 1 || typ == 3)

  return;
}
