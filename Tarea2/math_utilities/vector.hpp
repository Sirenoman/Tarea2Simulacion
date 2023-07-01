//Creacion de la clase Vector
class Vector{
    private:
        int size;
        float* data;

        void create(){
            data = (float*) malloc(sizeof(float)*size);
        }
    public:
        Vector(){}
        Vector(int data_qty){
            size = data_qty;
            create();
        }
        ~Vector(){
            free(data);
        }

        void init(){
            for(int i = 0; i < size;i++)
                data[i] = 0;
        }

        void setSize(int num_values){
            size = num_values;
            create();
        }

        int getSize(){
            return size;
        }

        void set(float value, int position){
            data[position] = value;
        }

        void add(float value , int position){
            data[position] += value;
        }
        //Obtener
        
        float get(int position){
            return data[position];
        }

        void removeRow(int row){
            int neoIndex = 0;
            float* neoData = (float*) malloc(sizeof(float)*(size-1));
            for(int i = 0; i < size; i++)
                if(i != row){
                    neoData[neoIndex] = data[i];
                    neoIndex++;
                }
            free(data);
            data = neoData;
            size--;
        }

        void show(){
            cout << "[ " << data[0];
            for(int i = 1; i < size; i++)
                cout << "; " << data[i];
            cout << " ]\n\n";
        }

};   