#include <iostream>
#include <string>

class OverseasStore{
private:
    std::string storeName;
public:
    OverseasStore(const std::string&name):storeName(name){}
    void buyItem(const std::string& itemName)const{
        std::cout<<"["<<storeName<<"] 已售出商品："<<itemName<<",金额已收到。\n";
    }
};

class Proxy{
private:
    OverseasStore store;//持有的真实商店
    double commissionRate;//代购费率

public:
    Proxy(const std::string& storeName,double rate=0.1)
    :store(storeName)
    ,commissionRate(rate)
    {}

    //客户通过代理购买商品
    void buyItem(const std::string& itemName,double originalPrice)const{
        std::cout<<"[代理]收到订单："<<itemName<<", 海外价"<<originalPrice<<"元。\n";

        //代理的额外工作：检查库存（模拟）
        std::cout<<"[代理]正在查询海外库存……\n";
        bool inStock=true;//假设有货
        if(!inStock){
            std::cout<<"[代理]缺货\n";
            return;
        }

        //计算代购费用
        double totalPrice=originalPrice*(1+commissionRate);
        std::cout<<"[代理]总费用："<<totalPrice<<std::endl;

        //调用真实商店购买
        store.buyItem(itemName);
        std::cout<<"[代理]已安排国际物流\n";
    }
};

int main(){
    std::cout<<"====代理模式演示：海外代购====\n\n";

    //创建代理对象（代购）
    Proxy proxy("美国Apple旗舰店",0.15);

    //客户通过代理购买
    proxy.buyItem("iPhone 15 pro",6999);
    std::cout<<"\n---------------\n\n";
    proxy.buyItem("AirPods Pro",1899.0);
    return 0;
}