// Mef_process.hpp
float calculate_local_volumen(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4)
{
    /*
        return abs(((x2 - x1)*(y3 - y1)*(z4 - z1) + (y2 - y1)*(z3 - z1)*(x4 - x1) + (z2 - z1)*(x3 - x1)*(y4 - y1))
            - ((z2 - z1)*(y3 - y1)*(x4 - x1) + (y2 - y1)*(x3 - x1)*(z4 - z1) + (x2 - x1)*(z3 - z1)*(y4 - y1)))/6;
    */
    return abs(((x2 - x1) * (y3 - y1) * (z4 - z1) + (y2 - y1) * (z3 - z1) * (x4 - x1) + (z2 - z1) * (x3 - x1) * (y4 - y1)) - ((z2 - z1) * (y3 - y1) * (x4 - x1) + (y2 - y1) * (x3 - x1) * (z4 - z1) + (x2 - x1) * (z3 - z1) * (y4 - y1))) / 6.0;
}

float calculate_local_jacobian(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4)
{
    return (x2 - x1) * (y3 - y1) * (z4 - z1) - (x2 - x1) * (y4 - y1) * (z3 - z1) - (x3 - x1) * (y2 - y1) * (z4 - z1) + (x3 - x1) * (y4 - y1) * (z2 - z1) + (x4 - x1) * (y2 - y1) * (z3 - z1) - (x4 - x1) * (y3 - y1) * (z2 - z1);
}

//Formula Ariel
void calculte_B(Matrix* B){
    B->set(-1,0,0); B->set(1,0,1); B->set(0,0,2); B->set(0,0,3);
    B->set(-1,1,0); B->set(0,1,1); B->set(1,1,2); B->set(0,1,3);
    B->set(-1,2,0); B->set(0,2,1); B->set(0,2,2); B->set(1,2,3);
}

void calculate_loca_A(Matrix* A, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3,float x4, float y4, float z4){
    A->set( (y3 - y1)*(z4 - z1) - (y4 - y1)*(z3 - z1), 0, 0);  A->set(-(x3 - x1)*(z4 - z1) + (x4 - x1)*(z3 - z1), 0, 1);  A->set( (x3 - x1)*(y4 - y1) - (x4 - x1)*(y3 - y1), 0, 2);
    A->set(-(y2 - y1)*(z4 - z1) + (y4 - y1)*(z2 - z1), 1, 0);  A->set( (x2 - x1)*(z4 - z1) - (x4 - x1)*(z2 - z1), 1, 1);  A->set(-(x2 - x1)*(y4 - y1) + (x4 - x1)*(y2 - y1), 1, 2);
    A->set( (y2 - y1)*(z3 - z1) - (y3 - y1)*(z2 - z1), 2, 0);  A->set(-(x2 - x1)*(z3 - z1) + (x3 - x1)*(z2 - z1), 2, 1);  A->set( (x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1), 2, 2);

}
void create_local_K(Matrix* K, short element_id,Mesh3D* M){
    K->setSize(4,4);
    float k = M->getProblemData(THERMAL_CONDUCTIVITY);
    float x1 = M->getElement(element_id)->get_node1()->get_x_coordinate(), y1 = M->getElement(element_id)->get_node1()->get_y_coordinate(), z1 = M->getElement(element_id)->get_node1()->get_z_coordinate(),
        x2 = M->getElement(element_id)->get_node2()->get_x_coordinate(), y2 = M->getElement(element_id)->get_node2()->get_y_coordinate(), z2 = M->getElement(element_id)->get_node2()->get_z_coordinate(),
        x3 = M->getElement(element_id)->get_node3()->get_x_coordinate(), y3 = M->getElement(element_id)->get_node3()->get_y_coordinate(), z3 = M->getElement(element_id)->get_node3()->get_z_coordinate(),
        x4 = M->getElement(element_id)->get_node4()->get_x_coordinate(), y4 = M->getElement(element_id)->get_node4()->get_y_coordinate(), z4 = M->getElement(element_id)->get_node4()->get_z_coordinate();
    float Volumen = calculate_local_volumen(x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4);
    float Jacobian = calculate_local_jacobian(x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4);

    //Asingar los tamaños de las matrices de B y A
    Matrix B(3,4), A(3,3);
    calculte_B(&B);
    calculate_loca_A(&A,x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4);
    //B.show(); A.show();

    Matrix Bt(4,3), At(3,3);
    transpose_matrix(&B,3,4,&Bt);
    transpose_matrix(&A,3,3,&At);
    //B.show(); A.show();

    //Duda sobre las variables resultados
    Matrix resultado1,resultado2,resultado3;
    product_matrix_by_matrix(&A,&B,&resultado1);
    product_matrix_by_matrix(&At,&resultado1,&resultado2);
    product_matrix_by_matrix(&Bt,&resultado2,&resultado3);
    //Formula de presentacion
    product_scalar_by_matrix(k*Volumen/(Jacobian*Jacobian),&resultado3,4,4,K);

    //cout << "\t\tLocal matrix created for Element " << element_id+1 << ": "; K->show(); cout << "\n";
}
void create_local_b(Vector* b, short element_id, Mesh3D*M){
    b->setSize(4);
    float Q = M->getProblemData(HEAT_SOURCE);
    float x1 = M->getElement(element_id)->get_node1()->get_x_coordinate(), y1 = M->getElement(element_id)->get_node1()->get_y_coordinate(), z1 = M->getElement(element_id)->get_node1()->get_z_coordinate(),
        x2 = M->getElement(element_id)->get_node2()->get_x_coordinate(), y2 = M->getElement(element_id)->get_node2()->get_y_coordinate(), z2 = M->getElement(element_id)->get_node2()->get_z_coordinate(),
        x3 = M->getElement(element_id)->get_node3()->get_x_coordinate(), y3 = M->getElement(element_id)->get_node3()->get_y_coordinate(), z3 = M->getElement(element_id)->get_node3()->get_z_coordinate(),
        x4 = M->getElement(element_id)->get_node4()->get_x_coordinate(), y4 = M->getElement(element_id)->get_node4()->get_y_coordinate(), z4 = M->getElement(element_id)->get_node4()->get_z_coordinate();
    float J = calculate_local_jacobian(x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4);

    //Establecer los valores 
    b->set(Q*J/24,0);
    b->set(Q*J/24,1);
    b->set(Q*J/24,2);
    b->set(Q*J/24,3);

    //cout << "\t\tLocal vector created for Element " << element_id+1 << ": "; b->show(); cout << "\n";
}
void create_local_systems(Matrix* Ks, Vector* bs, int num_elements, Mesh3D* M){
    for(int e = 0; e < num_elements; e++){
        cout << "\tCreating local system for Element " << e+1 << "...\n\n";
        create_local_K(&Ks[e],e,M);
        create_local_b(&bs[e],e,M);
    }
}
void assembly_K(Matrix* K, Matrix* local_K, short index1, short index2, short index3, int index4){
    K->add(local_K->get(0,0), index1, index1); K->add(local_K->get(0,1), index1, index2); K->add(local_K->get(0,2), index1, index3); K->add(local_K->get(0,3), index1, index4);
    K->add(local_K->get(1,0), index2, index1); K->add(local_K->get(1,1), index2, index2); K->add(local_K->get(1,2), index2, index3); K->add(local_K->get(1,3), index2, index4);
    K->add(local_K->get(2,0), index3, index1); K->add(local_K->get(2,1), index3, index2); K->add(local_K->get(2,2), index3, index3); K->add(local_K->get(2,3), index3, index4);
    K->add(local_K->get(3,0), index4, index1); K->add(local_K->get(3,1), index4, index2); K->add(local_K->get(3,2), index4, index3); K->add(local_K->get(3,3), index4, index4);
}
void assembly_b(Vector* b, Vector* local_b, short index1, short index2, short index3, int index4){
    b->add(local_b->get(0), index1);
    b->add(local_b->get(1), index2);
    b->add(local_b->get(2), index3);
    b->add(local_b->get(3), index4);
}
//Ensamblaje de las matrices y vectores locales a las matrices y vectores globales en 3D

void assembly(Matrix* K, Vector* b, Matrix* Ks, Vector* bs, short num_elements, Mesh3D* M){
    K->init();
    b->init();
    //K->show();
    //b->show();

    for(int e=0; e<num_elements;e++){
        cout<<"\tAssembling for Element"<<e+1<<".......\n\n";
        short index1 = M->getElement(e)->get_node1()->get_ID()-1;
        short index2 = M->getElement(e)->get_node2()->get_ID()-1;
        short index3 = M->getElement(e)->get_node3()->get_ID()-1;
        short index4 = M->getElement(e)->get_node4()->get_ID()-1;

        assembly_K(K, &Ks[e], index1, index2, index3, index4);
        assembly_b(b, &bs[e], index1, index2, index3, index4);

        //cout << "\t\t"; K->show(); cout << "\t\t"; b->show(); cout << "\n";

    }

}
//3D
void apply_neumann_boundary_conditions(Vector* b, Mesh3D* M){
    short num_conditions = M->getQuantity(NUM_NEUMANN);

    for(int c = 0; c<num_conditions;c++){
        Condition3D* condition = M->getNeumannCondition(c);

        short index = condition->getNode()->get_ID()-1;
        b->add(condition->get_value(),index);

    }
}

void add_column_to_RHS(Matrix* K, Vector* b,int col, float T_bar){
    for(int r = 0; r<K->getNrows();r++)
        b->add(-T_bar*K->get(r,col),r);
}
//3D
void apply_dirichlet_boundary_conditions(Matrix* K, Vector* b, Mesh3D* M){
    int num_conditions = M->getQuantity(NUM_DIRICHLET);
    int previous_removed = 0;

    for(int c = 0; c < num_conditions; c++){
        Condition3D* cond = M->getDirichletCondition(c);
        
        int index = cond->getNode()->get_ID() - 1 - previous_removed;
        float cond_value = cond->get_value();

        //K->show();
        K->removeRow(index);
        //K->show();
        //b->show();
        b->removeRow(index);
        //b->show();

        add_column_to_RHS(K, b, index, cond_value);
        //b->show();

        K->removeColumn(index);
        //K->show();

        previous_removed++;
    }
}

void solve_system(Matrix* K, Vector* b, Vector* T){
    int n = K->getNrows();
    Matrix Kinversa(n,n);
    cout << "*****\tCalculating inverse of global matrix******\n\n";
    calculate_inverse(K, n, &Kinversa);

    cout<<"*****\tPerforming final calculation******\n\n";
    product_matrix_by_vector(&Kinversa, b, n, n, T);
}
//3D
void merge_results_with_dirichlet(Vector* T, Vector* Tf, int n, Mesh3D* M){
    int num_dirichlet = M->getQuantity(NUM_DIRICHLET);

    int cont_dirichlet = 0;
    int cont_T = 0;
    for(int i = 0; i < n; i++){
        if(M->doesNodeHaveDirichletCondition(i+1)){
            Condition3D* cond = M->getDirichletCondition(cont_dirichlet);
            cont_dirichlet++;
        
            float cond_value = cond->get_value();

            Tf->set(cond_value,i);
        }else{
            Tf->set(T->get(cont_T),i);
            cont_T++;
        }
    }
}

