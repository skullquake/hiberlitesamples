#include<iostream>
#include<vector>
#include"hiberlite.h"
class Person_{//no hiberlite
public:
	std::string name;
        int age;
	std::vector<std::string> bio;
};
class Person{//hiberliteized
    friend class hiberlite::access;
    template<class Archive>
    void hibernate(Archive&ar)
    {
        ar & HIBERLITE_NVP(name);
        ar & HIBERLITE_NVP(age);
        ar & HIBERLITE_NVP(bio);
    }
public:
    std::string name;
    double age;
    std::vector<std::string>bio;
};
HIBERLITE_EXPORT_CLASS(Person)
int main(int argc,char**argv){
	std::cout<<"main:beg"<<std::endl;
	//open db
	hiberlite::Database db;
	db.open("a.db");
	//reg mod
	db.registerBeanClass<Person>();
	//mutate mod
	db.dropModel();
	db.createModel();
	for(int i=0;i<8;i++){//ex sav
		Person x;
		x.name="Person"+std::to_string(i);
		x.age=i;
		for(int j=0;j<4;j++){
			x.bio.push_back(std::string("bio ")+std::to_string(1900+j));
		}
		hiberlite::bean_ptr<Person>p=db.copyBean(x);
		x.age=-1; //no mutate record
		p->age=22;//mutate record
	}
	{//ex lod
		int pidx=0;
		int bidx=0;
		hiberlite::bean_ptr<Person> p=db.loadBean<Person>(pidx+1);
		std::cout<<"p[0]:"<<p->name<<","<<p->age<<std::endl;
		bidx=0;for(auto&b:p->bio){
			std::cout<<"p["<<pidx<<"]:bio["<<(bidx++)<<"]:"<<b<<std::endl;
		}
		std::vector< hiberlite::bean_ptr<Person>>v=db.getAllBeans<Person>();
		std::cout<<"found"<<v.size()<<" persons in the database\n";
		pidx=0;for(auto&p:v){
			std::cout << "p["<<(pidx++)<<"]:"<<p->name<<","<<p->age<<std::endl;
			bidx=0;for(auto&b:p->bio){
				std::cout<<"p["<<pidx<<"]:bio["<<(bidx++)<<"]"<<b<<std::endl;
			}
		}
	}
	std::cout<<"main:end"<<std::endl;
	return 0;
}
