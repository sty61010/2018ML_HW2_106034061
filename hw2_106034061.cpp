//
//  hw2_106034061.cpp
//  Program
//
//  Created by 曾靖渝 on 2018/10/14.
//  Copyright © 2018年 曾靖渝. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>
#include <math.h>
using namespace std;
using example = vector<double>;
class k_NN
{
private:
    set<example> Training_Set;
    vector<string> class_labels;
public:
    void add_to_trainingset(string class_label, example ex)//adding the examples into Training Set
    {
//        for(auto i:ex)
//            cout<<i<<" ";
//        cout<<class_label<<endl;
        bool found=false;
        for(int i=0;i<class_labels.size();i++)
        {
            if(class_labels[i]==class_label)
            {
                found=true;
                ex.push_back(i);
                break;
            }
        }
        if(!found)
        {
            ex.push_back(class_labels.size());
            class_labels.push_back(class_label);
        }
        Training_Set.insert(ex);
    }
    void print_Training_Set(void)//for debugging
    {
        for(auto s:Training_Set)
        {
            for(auto v:s)
                cout<<v<<"  ";
            cout<<endl;
        }
        
    }
    void print_class_labels(void)//for debugging
    {
        for(int i=0;i<class_labels.size();i++)
            cout<<"index:"<<i<<":"<<class_labels[i]<<endl;
    }
    double calculate_error(example ex1, example ex2)//to calculate the distance between two examples
    {
//        cout<<"=====calculating==========================="<<endl;
        double sum=0;
        for(int i=0;i<ex1.size()-1;i++)
        {
            sum+=pow((ex1[i]-ex2[i]),2);
        }
        
        sum=sqrt(sum);
        return sum;
    }
    string classfier(example ex)//the classfier
    {
        int index=0;
        double error=1000000;
        for(auto s:Training_Set)
        {
            double new_error=calculate_error(s, ex);
            if(error>=new_error)
            {
                index=s[s.size()-1];
                error=new_error;
//                cout<<"->refresh:index:"<<s[s.size()-1]<<":"<<class_labels[s[s.size()-1]]<<":error="<<error<<" ,new_error="<<new_error<<endl;
            }
//            else cout<<"->No refresh:"<<s[s.size()-1]<<":"<<class_labels[s[s.size()-1]]<<":error"<<error<<" ,new_error="<<new_error<<endl;

        }
//        cout<<"->Choose index:"<<index<<endl;
        return class_labels[index];
    }
};
int main(void)
{
    k_NN k_NN_classfier;
    int attribute_number;
//    cout<<"====input the number of attributes==========================\n";
    cin>>attribute_number;
//    cout<<"====input the number of instances=========================\n";
    int instance_number;
    cin>>instance_number;
    
    int training_number;
    int testing_number;
    
    double error_rate=0;
    int wrong_number=0;
    training_number=(int)(0.6*(double)instance_number);
    testing_number=instance_number-training_number;
    cout<<"Training Number:"<<training_number<<endl;
    cout<<"Testing Number:"<<testing_number<<endl;
    int i=0;
    cout<<"=====Training Set========================="<<endl;
    while(training_number--)
    {
        cout<<++i<<":";
        string input;
        example ex;
        double value;

        for(int i=0;i<attribute_number;i++)
        {
            cin>>value;
            ex.push_back(value);
            getchar();
        }
        cin>>input;
        k_NN_classfier.add_to_trainingset(input, ex);
//        getchar();
        if(input=="Done")break;
    }
    
//    cout<<"====the Training Set==========================\n";
//    k_NN_classfier.print_Training_Set();
//    cout<<"====the Class Labels==========================\n";
//    k_NN_classfier.print_class_labels();
//
    cout<<"====Testing Set========================="<<endl;
    i=0;
    while(testing_number--)
    {
        cout<<++i<<":";
        string input_x;
        
        example ex;
        double value;
        for(int i=0;i<attribute_number;i++)
        {
            cin>>value;
            ex.push_back(value);
            getchar();
        }
        cin>>input_x;
//        getchar();
        cout<<"====Classifying=========================="<<endl;
        string answer=k_NN_classfier.classfier(ex);
        cout<<"Answer: "<<input_x<<"->Classify to:"<<answer<<"\n====Done========================="<<endl;
        if(answer!=input_x)
        {
            cout<<"Wrong!!!!!!!!!"<<endl;
            wrong_number++;
        }
    }
    testing_number=(int)(0.4*(double)instance_number);
    error_rate=(double)wrong_number/(double)testing_number;
    cout<<"Wrong number:"<<wrong_number<<", Correct number"<<testing_number-wrong_number<<endl;
    cout<<"=====Error Rate :"<<error_rate<<"=========================="<<endl;
    return 0;
}
/*
 4
 50
 5.1,3.5,1.4,0.2,Iris-setosa
 4.9,3.0,1.4,0.2,Iris-setosa
 4.7,3.2,1.3,0.2,Iris-setosa
 4.6,3.1,1.5,0.2,Iris-setosa
 5.0,3.6,1.4,0.2,Iris-setosa
 5.4,3.9,1.7,0.4,Iris-setosa
 4.6,3.4,1.4,0.3,Iris-setosa
 5.0,3.4,1.5,0.2,Iris-setosa
 4.4,2.9,1.4,0.2,Iris-setosa
 4.9,3.1,1.5,0.1,Iris-setosa
 7.0,3.2,4.7,1.4,Iris-versicolor
 6.4,3.2,4.5,1.5,Iris-versicolor
 6.9,3.1,4.9,1.5,Iris-versicolor
 5.5,2.3,4.0,1.3,Iris-versicolor
 6.5,2.8,4.6,1.5,Iris-versicolor
 5.7,2.8,4.5,1.3,Iris-versicolor
 6.3,3.3,4.7,1.6,Iris-versicolor
 4.9,2.4,3.3,1.0,Iris-versicolor
 6.6,2.9,4.6,1.3,Iris-versicolor
 5.2,2.7,3.9,1.4,Iris-versicolor
 6.3,3.3,6.0,2.5,Iris-virginica
 5.8,2.7,5.1,1.9,Iris-virginica
 7.1,3.0,5.9,2.1,Iris-virginica
 6.3,2.9,5.6,1.8,Iris-virginica
 6.5,3.0,5.8,2.2,Iris-virginica
 7.6,3.0,6.6,2.1,Iris-virginica
 4.9,2.5,4.5,1.7,Iris-virginica
 7.3,2.9,6.3,1.8,Iris-virginica
 6.7,2.5,5.8,1.8,Iris-virginica
 7.2,3.6,6.1,2.5,Iris-virginica
 

 
 
 */

/*
 4
 150
 5.1,3.5,1.4,0.2,Iris-setosa
 4.9,3.0,1.4,0.2,Iris-setosa
 4.7,3.2,1.3,0.2,Iris-setosa
 4.6,3.1,1.5,0.2,Iris-setosa
 5.0,3.6,1.4,0.2,Iris-setosa
 5.4,3.9,1.7,0.4,Iris-setosa
 4.6,3.4,1.4,0.3,Iris-setosa
 5.0,3.4,1.5,0.2,Iris-setosa
 4.4,2.9,1.4,0.2,Iris-setosa
 4.9,3.1,1.5,0.1,Iris-setosa
 5.4,3.7,1.5,0.2,Iris-setosa
 4.8,3.4,1.6,0.2,Iris-setosa
 4.8,3.0,1.4,0.1,Iris-setosa
 4.3,3.0,1.1,0.1,Iris-setosa
 5.8,4.0,1.2,0.2,Iris-setosa
 5.7,4.4,1.5,0.4,Iris-setosa
 5.4,3.9,1.3,0.4,Iris-setosa
 5.1,3.5,1.4,0.3,Iris-setosa
 5.7,3.8,1.7,0.3,Iris-setosa
 5.1,3.8,1.5,0.3,Iris-setosa
 5.4,3.4,1.7,0.2,Iris-setosa
 5.1,3.7,1.5,0.4,Iris-setosa
 4.6,3.6,1.0,0.2,Iris-setosa
 5.1,3.3,1.7,0.5,Iris-setosa
 4.8,3.4,1.9,0.2,Iris-setosa
 5.0,3.0,1.6,0.2,Iris-setosa
 5.0,3.4,1.6,0.4,Iris-setosa
 5.2,3.5,1.5,0.2,Iris-setosa
 5.2,3.4,1.4,0.2,Iris-setosa
 4.7,3.2,1.6,0.2,Iris-setosa
 7.0,3.2,4.7,1.4,Iris-versicolor
 6.4,3.2,4.5,1.5,Iris-versicolor
 6.9,3.1,4.9,1.5,Iris-versicolor
 5.5,2.3,4.0,1.3,Iris-versicolor
 6.5,2.8,4.6,1.5,Iris-versicolor
 5.7,2.8,4.5,1.3,Iris-versicolor
 6.3,3.3,4.7,1.6,Iris-versicolor
 4.9,2.4,3.3,1.0,Iris-versicolor
 6.6,2.9,4.6,1.3,Iris-versicolor
 5.2,2.7,3.9,1.4,Iris-versicolor
 5.0,2.0,3.5,1.0,Iris-versicolor
 5.9,3.0,4.2,1.5,Iris-versicolor
 6.0,2.2,4.0,1.0,Iris-versicolor
 6.1,2.9,4.7,1.4,Iris-versicolor
 5.6,2.9,3.6,1.3,Iris-versicolor
 6.7,3.1,4.4,1.4,Iris-versicolor
 5.6,3.0,4.5,1.5,Iris-versicolor
 5.8,2.7,4.1,1.0,Iris-versicolor
 6.2,2.2,4.5,1.5,Iris-versicolor
 5.6,2.5,3.9,1.1,Iris-versicolor
 5.9,3.2,4.8,1.8,Iris-versicolor
 6.1,2.8,4.0,1.3,Iris-versicolor
 6.3,2.5,4.9,1.5,Iris-versicolor
 6.1,2.8,4.7,1.2,Iris-versicolor
 6.4,2.9,4.3,1.3,Iris-versicolor
 6.6,3.0,4.4,1.4,Iris-versicolor
 6.8,2.8,4.8,1.4,Iris-versicolor
 6.7,3.0,5.0,1.7,Iris-versicolor
 6.0,2.9,4.5,1.5,Iris-versicolor
 5.7,2.6,3.5,1.0,Iris-versicolor
 6.3,3.3,6.0,2.5,Iris-virginica
 5.8,2.7,5.1,1.9,Iris-virginica
 7.1,3.0,5.9,2.1,Iris-virginica
 6.3,2.9,5.6,1.8,Iris-virginica
 6.5,3.0,5.8,2.2,Iris-virginica
 7.6,3.0,6.6,2.1,Iris-virginica
 4.9,2.5,4.5,1.7,Iris-virginica
 7.3,2.9,6.3,1.8,Iris-virginica
 6.7,2.5,5.8,1.8,Iris-virginica
 7.2,3.6,6.1,2.5,Iris-virginica
 6.5,3.2,5.1,2.0,Iris-virginica
 6.4,2.7,5.3,1.9,Iris-virginica
 6.8,3.0,5.5,2.1,Iris-virginica
 5.7,2.5,5.0,2.0,Iris-virginica
 5.8,2.8,5.1,2.4,Iris-virginica
 6.4,3.2,5.3,2.3,Iris-virginica
 6.5,3.0,5.5,1.8,Iris-virginica
 7.7,3.8,6.7,2.2,Iris-virginica
 7.7,2.6,6.9,2.3,Iris-virginica
 6.0,2.2,5.0,1.5,Iris-virginica
 6.9,3.2,5.7,2.3,Iris-virginica
 5.6,2.8,4.9,2.0,Iris-virginica
 7.7,2.8,6.7,2.0,Iris-virginica
 6.3,2.7,4.9,1.8,Iris-virginica
 6.7,3.3,5.7,2.1,Iris-virginica
 7.2,3.2,6.0,1.8,Iris-virginica
 6.2,2.8,4.8,1.8,Iris-virginica
 6.1,3.0,4.9,1.8,Iris-virginica
 6.4,2.8,5.6,2.1,Iris-virginica
 7.2,3.0,5.8,1.6,Iris-virginica
 
 4.8,3.1,1.6,0.2,Iris-setosa
 5.4,3.4,1.5,0.4,Iris-setosa
 5.2,4.1,1.5,0.1,Iris-setosa
 5.5,4.2,1.4,0.2,Iris-setosa
 4.9,3.1,1.5,0.1,Iris-setosa
 5.0,3.2,1.2,0.2,Iris-setosa
 5.5,3.5,1.3,0.2,Iris-setosa
 4.9,3.1,1.5,0.1,Iris-setosa
 4.4,3.0,1.3,0.2,Iris-setosa
 5.1,3.4,1.5,0.2,Iris-setosa
 5.0,3.5,1.3,0.3,Iris-setosa
 4.5,2.3,1.3,0.3,Iris-setosa
 4.4,3.2,1.3,0.2,Iris-setosa
 5.0,3.5,1.6,0.6,Iris-setosa
 5.1,3.8,1.9,0.4,Iris-setosa
 4.8,3.0,1.4,0.3,Iris-setosa
 5.1,3.8,1.6,0.2,Iris-setosa
 4.6,3.2,1.4,0.2,Iris-setosa
 5.3,3.7,1.5,0.2,Iris-setosa
 5.0,3.3,1.4,0.2,Iris-setosa
 5.5,2.4,3.8,1.1,Iris-versicolor
 5.5,2.4,3.7,1.0,Iris-versicolor
 5.8,2.7,3.9,1.2,Iris-versicolor
 6.0,2.7,5.1,1.6,Iris-versicolor
 5.4,3.0,4.5,1.5,Iris-versicolor
 6.0,3.4,4.5,1.6,Iris-versicolor
 6.7,3.1,4.7,1.5,Iris-versicolor
 6.3,2.3,4.4,1.3,Iris-versicolor
 5.6,3.0,4.1,1.3,Iris-versicolor
 5.5,2.5,4.0,1.3,Iris-versicolor
 5.5,2.6,4.4,1.2,Iris-versicolor
 6.1,3.0,4.6,1.4,Iris-versicolor
 5.8,2.6,4.0,1.2,Iris-versicolor
 5.0,2.3,3.3,1.0,Iris-versicolor
 5.6,2.7,4.2,1.3,Iris-versicolor
 5.7,3.0,4.2,1.2,Iris-versicolor
 5.7,2.9,4.2,1.3,Iris-versicolor
 6.2,2.9,4.3,1.3,Iris-versicolor
 5.1,2.5,3.0,1.1,Iris-versicolor
 5.7,2.8,4.1,1.3,Iris-versicolor
 7.4,2.8,6.1,1.9,Iris-virginica
 7.9,3.8,6.4,2.0,Iris-virginica
 6.4,2.8,5.6,2.2,Iris-virginica
 6.3,2.8,5.1,1.5,Iris-virginica
 6.1,2.6,5.6,1.4,Iris-virginica
 7.7,3.0,6.1,2.3,Iris-virginica
 6.3,3.4,5.6,2.4,Iris-virginica
 6.4,3.1,5.5,1.8,Iris-virginica
 6.0,3.0,4.8,1.8,Iris-virginica
 6.9,3.1,5.4,2.1,Iris-virginica
 6.7,3.1,5.6,2.4,Iris-virginica
 6.9,3.1,5.1,2.3,Iris-virginica
 5.8,2.7,5.1,1.9,Iris-virginica
 6.8,3.2,5.9,2.3,Iris-virginica
 6.7,3.3,5.7,2.5,Iris-virginica
 6.7,3.0,5.2,2.3,Iris-virginica
 6.3,2.5,5.0,1.9,Iris-virginica
 6.5,3.0,5.2,2.0,Iris-virginica
 6.2,3.4,5.4,2.3,Iris-virginica
 5.9,3.0,5.1,1.8,Iris-virginica
 */




/*
 4
 5.1,3.5,1.4,0.2,Iris-setosa
 4.9,3.0,1.4,0.2,Iris-setosa
 4.7,3.2,1.3,0.2,Iris-setosa
 4.6,3.1,1.5,0.2,Iris-setosa
 5.0,3.6,1.4,0.2,Iris-setosa
 5.4,3.9,1.7,0.4,Iris-setosa
 4.6,3.4,1.4,0.3,Iris-setosa
 5.0,3.4,1.5,0.2,Iris-setosa
 4.4,2.9,1.4,0.2,Iris-setosa
 4.9,3.1,1.5,0.1,Iris-setosa
 5.4,3.7,1.5,0.2,Iris-setosa
 4.8,3.4,1.6,0.2,Iris-setosa
 4.8,3.0,1.4,0.1,Iris-setosa
 4.3,3.0,1.1,0.1,Iris-setosa
 5.8,4.0,1.2,0.2,Iris-setosa
 5.7,4.4,1.5,0.4,Iris-setosa
 5.4,3.9,1.3,0.4,Iris-setosa
 5.1,3.5,1.4,0.3,Iris-setosa
 5.7,3.8,1.7,0.3,Iris-setosa
 5.1,3.8,1.5,0.3,Iris-setosa
 5.4,3.4,1.7,0.2,Iris-setosa
 5.1,3.7,1.5,0.4,Iris-setosa
 4.6,3.6,1.0,0.2,Iris-setosa
 5.1,3.3,1.7,0.5,Iris-setosa
 4.8,3.4,1.9,0.2,Iris-setosa
 5.0,3.0,1.6,0.2,Iris-setosa
 5.0,3.4,1.6,0.4,Iris-setosa
 5.2,3.5,1.5,0.2,Iris-setosa
 5.2,3.4,1.4,0.2,Iris-setosa
 4.7,3.2,1.6,0.2,Iris-setosa
 4.8,3.1,1.6,0.2,Iris-setosa
 5.4,3.4,1.5,0.4,Iris-setosa
 5.2,4.1,1.5,0.1,Iris-setosa
 5.5,4.2,1.4,0.2,Iris-setosa
 4.9,3.1,1.5,0.1,Iris-setosa
 5.0,3.2,1.2,0.2,Iris-setosa
 5.5,3.5,1.3,0.2,Iris-setosa
 4.9,3.1,1.5,0.1,Iris-setosa
 4.4,3.0,1.3,0.2,Iris-setosa
 5.1,3.4,1.5,0.2,Iris-setosa
 5.0,3.5,1.3,0.3,Iris-setosa
 4.5,2.3,1.3,0.3,Iris-setosa
 4.4,3.2,1.3,0.2,Iris-setosa
 5.0,3.5,1.6,0.6,Iris-setosa
 5.1,3.8,1.9,0.4,Iris-setosa
 4.8,3.0,1.4,0.3,Iris-setosa
 5.1,3.8,1.6,0.2,Iris-setosa
 4.6,3.2,1.4,0.2,Iris-setosa
 5.3,3.7,1.5,0.2,Iris-setosa
 5.0,3.3,1.4,0.2,Iris-setosa
 7.0,3.2,4.7,1.4,Iris-versicolor
 6.4,3.2,4.5,1.5,Iris-versicolor
 6.9,3.1,4.9,1.5,Iris-versicolor
 5.5,2.3,4.0,1.3,Iris-versicolor
 6.5,2.8,4.6,1.5,Iris-versicolor
 5.7,2.8,4.5,1.3,Iris-versicolor
 6.3,3.3,4.7,1.6,Iris-versicolor
 4.9,2.4,3.3,1.0,Iris-versicolor
 6.6,2.9,4.6,1.3,Iris-versicolor
 5.2,2.7,3.9,1.4,Iris-versicolor
 5.0,2.0,3.5,1.0,Iris-versicolor
 5.9,3.0,4.2,1.5,Iris-versicolor
 6.0,2.2,4.0,1.0,Iris-versicolor
 6.1,2.9,4.7,1.4,Iris-versicolor
 5.6,2.9,3.6,1.3,Iris-versicolor
 6.7,3.1,4.4,1.4,Iris-versicolor
 5.6,3.0,4.5,1.5,Iris-versicolor
 5.8,2.7,4.1,1.0,Iris-versicolor
 6.2,2.2,4.5,1.5,Iris-versicolor
 5.6,2.5,3.9,1.1,Iris-versicolor
 5.9,3.2,4.8,1.8,Iris-versicolor
 6.1,2.8,4.0,1.3,Iris-versicolor
 6.3,2.5,4.9,1.5,Iris-versicolor
 6.1,2.8,4.7,1.2,Iris-versicolor
 6.4,2.9,4.3,1.3,Iris-versicolor
 6.6,3.0,4.4,1.4,Iris-versicolor
 6.8,2.8,4.8,1.4,Iris-versicolor
 6.7,3.0,5.0,1.7,Iris-versicolor
 6.0,2.9,4.5,1.5,Iris-versicolor
 5.7,2.6,3.5,1.0,Iris-versicolor
 5.5,2.4,3.8,1.1,Iris-versicolor
 5.5,2.4,3.7,1.0,Iris-versicolor
 5.8,2.7,3.9,1.2,Iris-versicolor
 6.0,2.7,5.1,1.6,Iris-versicolor
 5.4,3.0,4.5,1.5,Iris-versicolor
 6.0,3.4,4.5,1.6,Iris-versicolor
 6.7,3.1,4.7,1.5,Iris-versicolor
 6.3,2.3,4.4,1.3,Iris-versicolor
 5.6,3.0,4.1,1.3,Iris-versicolor
 5.5,2.5,4.0,1.3,Iris-versicolor
 5.5,2.6,4.4,1.2,Iris-versicolor
 6.1,3.0,4.6,1.4,Iris-versicolor
 5.8,2.6,4.0,1.2,Iris-versicolor
 5.0,2.3,3.3,1.0,Iris-versicolor
 5.6,2.7,4.2,1.3,Iris-versicolor
 5.7,3.0,4.2,1.2,Iris-versicolor
 5.7,2.9,4.2,1.3,Iris-versicolor
 6.2,2.9,4.3,1.3,Iris-versicolor
 5.1,2.5,3.0,1.1,Iris-versicolor
 5.7,2.8,4.1,1.3,Iris-versicolor
 6.3,3.3,6.0,2.5,Iris-virginica
 5.8,2.7,5.1,1.9,Iris-virginica
 7.1,3.0,5.9,2.1,Iris-virginica
 6.3,2.9,5.6,1.8,Iris-virginica
 6.5,3.0,5.8,2.2,Iris-virginica
 7.6,3.0,6.6,2.1,Iris-virginica
 4.9,2.5,4.5,1.7,Iris-virginica
 7.3,2.9,6.3,1.8,Iris-virginica
 6.7,2.5,5.8,1.8,Iris-virginica
 7.2,3.6,6.1,2.5,Iris-virginica
 6.5,3.2,5.1,2.0,Iris-virginica
 6.4,2.7,5.3,1.9,Iris-virginica
 6.8,3.0,5.5,2.1,Iris-virginica
 5.7,2.5,5.0,2.0,Iris-virginica
 5.8,2.8,5.1,2.4,Iris-virginica
 6.4,3.2,5.3,2.3,Iris-virginica
 6.5,3.0,5.5,1.8,Iris-virginica
 7.7,3.8,6.7,2.2,Iris-virginica
 7.7,2.6,6.9,2.3,Iris-virginica
 6.0,2.2,5.0,1.5,Iris-virginica
 6.9,3.2,5.7,2.3,Iris-virginica
 5.6,2.8,4.9,2.0,Iris-virginica
 7.7,2.8,6.7,2.0,Iris-virginica
 6.3,2.7,4.9,1.8,Iris-virginica
 6.7,3.3,5.7,2.1,Iris-virginica
 7.2,3.2,6.0,1.8,Iris-virginica
 6.2,2.8,4.8,1.8,Iris-virginica
 6.1,3.0,4.9,1.8,Iris-virginica
 6.4,2.8,5.6,2.1,Iris-virginica
 7.2,3.0,5.8,1.6,Iris-virginica
 7.4,2.8,6.1,1.9,Iris-virginica
 7.9,3.8,6.4,2.0,Iris-virginica
 6.4,2.8,5.6,2.2,Iris-virginica
 6.3,2.8,5.1,1.5,Iris-virginica
 6.1,2.6,5.6,1.4,Iris-virginica
 7.7,3.0,6.1,2.3,Iris-virginica
 6.3,3.4,5.6,2.4,Iris-virginica
 6.4,3.1,5.5,1.8,Iris-virginica
 6.0,3.0,4.8,1.8,Iris-virginica
 6.9,3.1,5.4,2.1,Iris-virginica
 6.7,3.1,5.6,2.4,Iris-virginica
 6.9,3.1,5.1,2.3,Iris-virginica
 5.8,2.7,5.1,1.9,Iris-virginica
 6.8,3.2,5.9,2.3,Iris-virginica
 6.7,3.3,5.7,2.5,Iris-virginica
 6.7,3.0,5.2,2.3,Iris-virginica
 6.3,2.5,5.0,1.9,Iris-virginica
 6.5,3.0,5.2,2.0,Iris-virginica
 6.2,3.4,5.4,2.3,Iris-virginica
 5.9,3.0,5.1,1.8,Iris-virginica
 1 1 1 1 Done
 */
