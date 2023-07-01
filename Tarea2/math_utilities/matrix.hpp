#include <stdio.h>
//Matrix in 3D
class Matrix{
    private:
        int nrows, ncols;
        float** data;

        void create(){
            data = (float**) malloc(sizeof(float*)*nrows);
            for(int r = 0; r<nrows;r++)
                data[r] = (float*) malloc(sizeof(float)*ncols);
        }

    public:
        Matrix(){}
        Matrix(int rows, int cols){
            nrows = rows;
            ncols = cols;
            create();
        }
        ~Matrix(){
            for(int r = 0; r<nrows;r++)
                free(data[r]);
            free(data);
        }

        void init(){
            for(int r = 0; r<nrows;r++)
                for(int c = 0; c<ncols;c++)
                    data[r][c] = 0;
        }
        
        void setSize(int rows, int cols){
            nrows = rows;
            ncols = cols;
            create();
        }
        int getNrows(){
            return nrows;
        }
        int getNcols(){
            return ncols;
        }

        //Funciones para establecer y obtener valores de la Matriz
        void set(float value, int row, int col){
            data[row][col] = value;
        }

        void add(float value, int row, int col){
            data[row][col] += value;
        }
        //Obteniendo los datos y colocandolos en la matriz

        float get(int row, int col){
            return data[row][col];
        }

        void removeRow(int row){
            int neoIndex = 0;
            float** neoData = (float**) malloc(sizeof(float*)*(nrows-1));
            for(int i = 0; i < nrows;i++){
                if(i != row){
                    neoData[neoIndex] = data[i];
                    neoIndex++;
                }
            }
            free(data[row]);
            free(data);
            data = neoData;
            nrows--;
        }

        void removeColumn(int col){
            int neoIndex = 0;
            float** neoData = (float**) malloc(sizeof(float*) * nrows);
            for(int r = 0; r < nrows; r++)
                neoData[r] = (float*) malloc(sizeof(float) * (ncols-1));

            for(int r = 0; r < nrows; r++){
                for(int c = 0; c < ncols; c++)
                    if(c != col){
                        neoData[r][neoIndex] = data[r][c];
                        neoIndex++;
                    }
                neoIndex = 0;
            }
            //printf("remove_column: %p - %p\n",data[0],data);
            for(int r = 0; r < nrows; r++)
                free(data[r]);
            free(data);
            data = neoData;
            ncols--;
        }


        void clone(Matrix* other){
            for(int rows = 0 ; rows < nrows; rows++)
                for(int cols = 0; cols < ncols; cols++)
                   other->set(data[rows][cols],rows,cols);
        }

        void show(){
            cout << "[";
            for(int rows = 0; rows < nrows ; rows++){
                cout << "[" << data[rows][0];
                for(int cols = 1; cols<ncols; cols++){
                    cout << ", " << data[rows][cols];
                }
                cout << "]" << endl;
            }
            cout << "]\n\n\n";
                
        }        
};