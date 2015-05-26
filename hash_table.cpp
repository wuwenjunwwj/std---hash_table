#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <utility>   
template<typename key_type, typename value_type>
struct Bucket_Node{
	key_type key;
	std::list< std::pair<key_type,value_type> >* value_list;
	bool list_empty;
	};

template<typename key_type, typename value_type>
class hash_table{
	public:
		hash_table(){
			int default_buckets = 5;
			this -> bucket = (Bucket_Node<key_type,value_type>*) malloc (default_buckets * sizeof(Bucket_Node<key_type, value_type>));
			bzero(bucket, default_buckets);
			bucket_count = default_buckets;
			bucket_actually = 0;
			rehash_factor = 0.6;
			bucket_init(bucket_count);
			};
		void bucket_init(int bucket_count){
			for(int i=0; i<bucket_count; i++){
				bucket[i].list_empty = true;
				bucket[i].value_list = new std::list< std::pair<key_type, value_type> >;
				}
			};
		void insert(std::pair<key_type, value_type> val){
			if(need_rehash()){
				std::cout<< "need rehash"<<std::endl;
				bucket_count = bucket_count << 1;
				copy_bucketdata();
				}
				int bucket_index = hash_func(val.first);
				if(bucket[bucket_index].list_empty){
					bucket[bucket_index].list_empty = false;
					bucket_actually ++;
					}
				(bucket[bucket_index].value_list)->push_back(val);
			};
		void find(key_type key){
			};
		void erase(){
			};
		void clear(){
			};
		//void operator=(){
		//	};
		//void operator[](){
		//	};

	private:
		Bucket_Node<key_type, value_type>* bucket;
		int bucket_count;
		int bucket_actually;
		double rehash_factor;
		int hash_func(key_type key){
			return key%bucket_count;	
			};
		bool need_rehash(){
			if( bucket_actually >= rehash_factor*bucket_count) {
				bucket_actually = 0;
				return true;
				}
			return false;
			};
		Bucket_Node<key_type, value_type>* copy_bucketdata(){
			 std::cout<<"copy old bucket to new"<<std::endl;
			 Bucket_Node<key_type, value_type>* bucket_new = (Bucket_Node<key_type,value_type>*) malloc (bucket_count * sizeof(Bucket_Node<key_type, value_type>));
			 bzero(bucket_new, bucket_count);
			 Bucket_Node<key_type, value_type>* bucket_old = bucket;
			 int bucket_count_old = bucket_count/2;
			 bucket = bucket_new;
			 bucket_init(bucket_count);
			 for(int i=0; i< (bucket_count_old); i++){
				if(!bucket_old[i].list_empty){
					for ( typename std::list< std::pair<key_type,value_type> >::iterator it=(bucket_old[i].value_list)-> begin(); it != (bucket_old[i].value_list) -> end(); ++it){
						insert(*it);
					}
				}
			}
			delete bucket_old;
			std::cout<<"copy done"<<std::endl;

		}
		
	};
int main(){
	hash_table<char, char>  hash_table_;
	hash_table_.insert(std::make_pair('a','b'));
	hash_table_.insert(std::make_pair('a','b'));
	hash_table_.insert(std::make_pair('a','c'));
	hash_table_.insert(std::make_pair('e','c'));
	hash_table_.insert(std::make_pair('f','c'));
	hash_table_.insert(std::make_pair('g','c'));
	hash_table_.insert(std::make_pair('z','c'));
	hash_table_.insert(std::make_pair('h','c'));
	hash_table_.insert(std::make_pair('j','c'));
	int bucket_num;
	return 0;
	};
