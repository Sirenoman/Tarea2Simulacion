#include <fstream>
//Archivo de input_output

void read_input(string filename, Mesh3D* M){
    string line;
    float k, Q, T_bar, T_hat;
    short num_nodes, num_elements, num_dirichlet, num_neumann;
    ifstream dat_file(filename + ".dat");

    dat_file  >> k >> Q >> T_bar >> T_hat >> num_nodes >> num_elements >> num_dirichlet >> num_neumann;

    M->setProblemData(k, Q);
    M->setQuantities(num_nodes, num_elements, num_dirichlet, num_neumann);

    M->initArrays();

    dat_file >> line;

    for(int i = 0; i < num_nodes;i++){
        short id;
        float x,y,z;
        dat_file >> id >> x >> y >> z;
        M->insertNode(new Node(id,x,y,z), i);
    }
    for(int i=0; i < num_nodes; i++){
        cout << M->getNode(i)->get_ID() << " " << M->getNode(i)->get_x_coordinate() << " " << M->getNode(i)->get_y_coordinate()<< " " << M->getNode(i)->get_z_coordinate() << "\n";
    }

    dat_file >> line >> line;

    for(int i = 0; i < num_elements; i++){
        short id, node1_id, node2_id, node3_id, node4_id;
        dat_file >> id >> node1_id >> node2_id >> node3_id >> node4_id;
        M-> insertElement(new Element3D(id,M->getNode(node1_id-1),M->getNode(node2_id-1),M->getNode(node3_id-1),M->getNode(node4_id-1)),i);
    }

    //Dirichlet
    dat_file >> line >> line;
    for(int i = 0; i<num_dirichlet;i++){
        short id;
        dat_file >> id;
        M-> insertDirichletCondition(new Condition3D(M->getNode(id-1),T_bar),i);
    }
    //Neumann
    dat_file >> line >>line;
    for(int i = 0; i<num_neumann;i++){
        short id;
        dat_file >> id;
        M-> insertNeumannCondition(new Condition3D(M->getNode(id-1),T_hat),i);
    }

    dat_file.close();
}

//funcion para escribir el archivo de salida
void write_output(string filename, Vector* T){
    ofstream res_file(filename + ".post.res");

    res_file << "GiD Post Results File 1.0\n";

    //Necesitamos crear el archivo Vector
    int n = T -> getSize();

    res_file << "Result \"Temperature\" \"Load Case 1\" " << 1 << " Scalar OnNodes\n";
    res_file << "ComponentNames \"T\"\n";
    res_file << "Values\n";

    for(int i = 0; i < n ; i++) {
        res_file << i + 1 << " " << T -> get(i) << "\n";
    }
    res_file << "End values\n";

    res_file.close();

}

