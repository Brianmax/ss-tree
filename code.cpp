#include<bits/stdc++.h>
using namespace std;
template <typename>
class Timer;

template <typename R, typename... T>
class Timer<R(T...)> {
 public:
  typedef R (*function_type)(T...);
  function_type function;

  explicit Timer(function_type function, std::string process_name = "")
      : function_(function), process_name_(process_name) {}

  R operator()(T... args) {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    R result = function_(std::forward<T>(args)...);

    end = std::chrono::high_resolution_clock::now();
    int64_t duration =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
            .count();

    std::cout << std::setw(10) << process_name_ << std::setw(30)
              << "Duration: " + std::to_string(duration) + " ns\n";
    return result;
  }

 private:
  function_type function_;
  std::string process_name_;
};
template<class T, class R>
float distance(vector<T> point1, vector<R> point2)
{
    int len = point1.size();
    float ans = 0;
    float temp = 0;
    for(int i = 0; i < len; i++)
    {
        ans = ans + pow((point1[i]-point2[i]),2);
    }
    ans = sqrt(ans);
    return ans;
}
vector<float> meanC(vector<vector<float>> centroids)
{
    int dimension = centroids[0].size();
    int len = centroids.size();
    vector<float> newCentroid;
    for(int i = 0; i < dimension; i++)
    {
        float media = 0;
        for(int e = 0; e < len; e++)
        {
            vector<float> CurrentCentroid = centroids[e];
            media = media + CurrentCentroid[i];
        }
        media = media/len;
        newCentroid.push_back(media);
    }
    return newCentroid;
}
float variance(vector<vector<float>> centroids, size_t axis)
{
    float mean = 0;
    int len = centroids.size();
    for(size_t i = 0; i < len; i++)
        mean = mean + centroids[i][axis];
    mean = mean/len;
    float var = 0;
    for(int i = 0; i < len; i++)
        var = var + pow(centroids[i][axis]-mean,2);
    var = var/len;
    return var;
}
template<class T>
vector<vector<float>> getRangeVector(int i, int f, vector<T> points)
{
    vector<vector<float>> answer;
    for(int index = i; index < f; index++)
        answer.push_back(points[index]);
    return answer;
}
int minVarianceSplit(vector<vector<float>> centroids, int indexD, int M, int m)
{
    float minVariance = numeric_limits<float>::max();
    int indexSplit= 0;
    for(int i = m; i < (M+1)-m; i++)
    {
        vector<vector<float>> VectorVar1 = getRangeVector(0, m, centroids);
        vector<vector<float>> VectorVar2 = getRangeVector(m, M+1, centroids);
        vector<vector<float>> cent;
        float variance1 = variance(VectorVar1, indexD);
        float variance2 = variance(VectorVar2, indexD);
        if(variance1 + variance2 < minVariance){
            minVariance = variance1 + variance2;
            indexSplit = i;
        }
    }
    return indexSplit;
}
void print_mnist(vector<float> point)
{
    int index = 0;
    for(int i = 0; i<28; i++)
    {
        for(int e = 0; e < 28; e++)
        {
            cout<<point[index++];
        }
        cout<<endl;
    }
}
template<int M, int m>
class SSNode
{
    public:
        float radio = 0;
        vector<float> centroid;
        vector<SSNode<M,m> *> childs;
        vector<vector<float>> points;
        bool isLeaf;
        SSNode<M,m> * findClosestChild(vector<float> point);
        void updateBounding();
        vector<vector<float>> getCentroids();
        pair<SSNode<M,m> *, SSNode<M,m> *> split(SSNode<M,m> *node);
        float radioFunction();
        int directionMaxVariance(SSNode<M,m> *node, vector<vector<float>> cntrds);
        int findSplitIndex(SSNode<M,m> *node, vector<vector<float>> &);
        bool intersectionPoint(vector<float> point);
        vector<pair<float, SSNode<M,m> *>> sortByDistance(vector<float> point);
        SSNode(bool leaf, vector<vector<float>> p,
        vector<SSNode<M,m> *> c)
        {
            isLeaf = leaf;
            points = p;
            childs = c;
        }
};
template<int M,int m>
bool SSNode<M,m>::intersectionPoint(vector<float> point)
{
    return distance(this->centroid, point)<=this->radio;
}
bool sortbysec(const pair<int,int> &a, const pair<int,int> &b)
{
    return (a.second < b.second);
}
template<int M, int m>
vector<pair<float, SSNode<M,m> *>> SSNode<M,m>::sortByDistance(vector<float> point)
{
    int len = this->childs.size();
    vector<SSNode<M,m> *> childs_ = this->childs;
    vector<pair<float, SSNode<M,m> *>> sorted;
    for(int i = 0; i < len; i++)
    {
        float dist = distance(childs_[i]->centroid, point);
        pair<float, SSNode<M,m> *> p;
        p.first = dist;
        p.second =childs_[i];
        sorted.push_back(p);
    }
    sort(sorted.begin(), sorted.end());
    return sorted;
}
template<int M, int m>
float SSNode<M,m>::radioFunction()
{
    int len = this->points.size();
    float maxDistance = 0;
    for(int i = 0; i < len; i++)
    {
        vector<float> point = this->points[i];
        for(int e = 0; e < len; e++)
        {
            int tmp = distance(point, this->points[e]);
            if(maxDistance < tmp)
                maxDistance = tmp;
        }
    }
    return maxDistance;
}
template<int M, int m>
int SSNode<M,m>::directionMaxVariance(SSNode<M,m> *node, vector<vector<float>> cntrds)
{
    float maxVariance = 0;
    int direction = 0;
    int len2 = cntrds[0].size();
    int len1 = cntrds.size();
    for(int i = 0; i < len1; i++)
    {
        for(int e = 0; e < len2; e++)
        {
            float tmp = variance(cntrds, e);
            if(maxVariance < tmp)
            {
                maxVariance = tmp;
                direction = e;
            }
        }
    }
    return direction;
}
template<int M, int m>
pair<vector<SSNode<M,m> *>,vector<SSNode<M,m> *>> getPartitionsNode(int indexSplit,
vector<vector<float>> SortC, SSNode<M,m> * node)
{
    vector<vector<float>> newPointsPosition;
    newPointsPosition = SortC;
    vector<SSNode<M,m> *> newChildsPositions(M+1,nullptr);
    vector<SSNode<M,m> *> aux = node->childs;
    for(int i = 0; i < aux.size(); i++)
    {
        SSNode<M,m> *innerNode = aux[i];
        for(int e = 0; e < newPointsPosition.size(); e++)
        {
            if(innerNode->centroid == newPointsPosition[e])
            {
                newChildsPositions[e] = innerNode;
                break;
            }
        }
    }
    node->childs = newChildsPositions;
    pair<vector<SSNode<M,m>*>,vector<SSNode<M,m>*>> partitions;
    vector<SSNode<M,m>*> part1;
    vector<SSNode<M,m>*> part2;
    //int minSplitIndex = minVarianceSplit(newPointsPosition,index,M,m);
    for(int i = 0; i < indexSplit; i++)
        part1.push_back(newChildsPositions[i]);
    for(int i = indexSplit; i < M+1; i++)
        part2.push_back(newChildsPositions[i]);
    partitions.first = part1; partitions.second = part2;
    return partitions;
}
template<int M, int m>
pair<vector<vector<float>>,vector<vector<float>>> getPartitionsLeaf(int indexSplit, vector<vector<float>> SortC, 
SSNode<M,m> *node)
{
    vector<vector<float>> newPointsPosition = SortC;
    vector<SSNode<M,m> *> newChildsPositions;
    //int minSplitIndex = minVarianceSplit(newPointsPosition, index,M,m);
    pair<vector<vector<float>>,vector<vector<float>>> partitions;
    vector<vector<float>> part1;
    vector<vector<float>> part2;
    for(int i = 0; i < indexSplit; i++)
        part1.push_back(newPointsPosition[i]);
    for(int i = indexSplit; i < M+1; i++)
        part2.push_back(newPointsPosition[i]);
    partitions.first = part1; partitions.second = part2;
    return partitions;
}
template<int M, int m>
int SSNode<M,m>::findSplitIndex(SSNode<M,m> *node, vector<vector<float>> &sortC)
{
    int CoordIndex = node->directionMaxVariance(node, sortC);
    vector<vector<float>> Centroids;
    //Centroids = node->getCentroids();
    std::sort(sortC.begin(), sortC.end(), [CoordIndex](vector<float> i, vector<float> j)
    { return (i)[CoordIndex] < (j)[CoordIndex]; });
    int indexSplit = minVarianceSplit(sortC, CoordIndex, M,m);
    return indexSplit;
}
template<int M, int m>
pair<SSNode<M,m> *, SSNode<M,m> *> SSNode<M,m>::split(SSNode<M,m> *node)
{
    vector<vector<float>> CentroidsNode;
    CentroidsNode = node->getCentroids();
    int splitIndex = findSplitIndex(node, CentroidsNode);
    //vector<vector<float>> centroids = node->getCentroids();
    SSNode<M,m> *pointer1,*pointer2;
    if(!node->isLeaf)
    {
        pair<vector<SSNode<M,m> *>,vector<SSNode<M,m> *>> partition;
        partition = getPartitionsNode(splitIndex, CentroidsNode, node);
        vector<vector<float>> fakePoints;
        pointer1 = new SSNode<M,m>(0,fakePoints, partition.first);
        pointer2 = new SSNode<M,m>(0,fakePoints, partition.second);
    }
    else
    {
        pair<vector<vector<float>>,vector<vector<float>>> partition;
        partition = getPartitionsLeaf(splitIndex, CentroidsNode, node);
        vector<SSNode<M,m>* > fakeChilds;
        pointer1 = new SSNode<M,m>(1,partition.first, fakeChilds);
        pointer2 = new SSNode<M,m>(1,partition.second, fakeChilds);
    }
    pointer1->updateBounding();
    pointer2->updateBounding();
    pair<SSNode<M,m> *, SSNode<M,m> *> splitedNodes;
    splitedNodes.first = pointer1;
    splitedNodes.second = pointer2;
    return splitedNodes;
}
template<int M, int m>
class SSTree
{
    public:
        SSNode<M,m> *root = nullptr;
        SSNode<M,m> * search(SSNode<M,m> *node, vector<float> point);
        void insert(vector<float> point);
        SSNode<M,m> * searchParentLeafMethod(queue<SSNode<M,m> *> &q, vector<float> point);
        pair<SSNode<M,m> *, SSNode<M,m> *> split();
        SSTree()
        {
            vector<vector<float>> f;
            vector<SSNode<M,m> *> g;
            root = new SSNode<M,m>(1, f, g);
        }
};
template<int M, int m>
vector<vector<float>> SSNode<M,m>::getCentroids()
{
    vector<vector<float>> centroids;
    vector<SSNode<M,m> *> c;
    int len = 0;
    if(this->isLeaf)
    {
        len = this->points.size();
        for(int i = 0; i < len; i++)
        {
            vector<float> f(this->points[i].begin(), this->points[i].end());
            centroids.push_back(f);
        }
        return centroids;
    }
    len = this->childs.size();
    for(int i = 0; i < len; i++)
    {
        SSNode<M,m> *tmp = this->childs[i];
        centroids.push_back(tmp->centroid);
    }
    return centroids;
}
template<int M, int m>
void SSNode<M,m>::updateBounding()
{
    vector<vector<float>> centroids = this->getCentroids();
    vector<float> newCentroid = meanC(centroids);
    vector<SSNode<M,m> *> childs_;
    vector<vector<float>> childPoints;
    if(this->isLeaf)
        childPoints = this->points;
    else
        childs_ = this->childs;
    float newRadio = 0;
    int len = centroids.size();
    float radio = 0;
    if(this->isLeaf)
    {
        for(int i = 0; i < len; i++)
        {
            float tmp = distance(newCentroid, points[i]);
            if(newRadio < tmp)
                newRadio = tmp;
        }
    }
    else
    {
        for(int i = 0; i < len; i++)
        {
            SSNode<M,m> *c = childs_[i];
            float tmp = distance(newCentroid, c->centroid);
            if(newRadio < tmp)
            {
                newRadio = tmp + c->radio;
            }
        }
    }
    this->radio = newRadio;
    this->centroid = newCentroid;
}
template<int M, int m>
SSNode<M,m> * SSNode<M,m>::findClosestChild(vector<float> point)
{
    SSNode<M, m> *choseNode;
    if(this->isLeaf)
        return this;
    else
    {
        int len = this->childs.size();
        int min = INT_MAX;
        SSNode<M,m> *child;
        for(int i = 0; i < len; i++)
        {
            child = this->childs[i];
            int newMin = distance(point, child->centroid);
            if(newMin < min)
            {
                min = newMin;
                choseNode = child;
            }
        }
    }
    return choseNode;
}
template<int M, int m>
SSNode<M,m> * SSTree<M,m>::search(SSNode<M,m> *node, vector<float> point)
{
    if(node->isLeaf)
    {
        int len = node->points.size();
        for(int i = 0; i < len; i++)
        {
            if(point == node->points[i])
            {
                print_mnist(node->points[i]);
                return node;
            }
        }
    }
    else
    {
        int len = node->childs.size();
        for(int i = 0; i < len; i++)
        {
            SSNode<M,m> *ans;
            if(node->intersectionPoint(point))
            {
                ans = search(node->childs[i],point);
                if(ans!=nullptr)
                {
                    return ans;
                }
            }
        }
    }
    return nullptr;
}
template<int M, int m>
SSNode<M,m> * SSTree<M,m>::searchParentLeafMethod(queue<SSNode<M,m> *> &Spheres, vector<float> point)
{
    queue<SSNode<M,m> *> q;
    SSNode<M,m> *ptr;
    ptr = root;
    Spheres.push(root);
    while (!ptr->isLeaf)
    {
        SSNode<M,m> *child;
        child = ptr->findClosestChild(point);
        Spheres.push(child);
        ptr = child;
    }
    return ptr;
}
template<int M, int m>
bool isThere(vector<float> point, SSNode<M,m> *node)
{
    int len = node->childs.size();
    for(int i = 0; i < len; i++)
    {
        if(point == node->points[i])
            return true;
    }
    return false;
}
template<int M, int m>
pair<SSNode<M,m> *,SSNode<M,m> *> insertUtil(vector<float> point, SSNode<M,m> *&node)
{
    if(node->isLeaf)
    {
        if(isThere(point, node))
        {
            pair<SSNode<M,m> *,SSNode<M,m> *> p;
            p.first = nullptr;
            p.second = nullptr;
            return p;
        }
        node->points.push_back(point);
        node->updateBounding();
        if(node->points.size() <= M)
        {
            pair<SSNode<M,m> *,SSNode<M,m> *> p;
            p.first = nullptr;
            p.second = nullptr;
            return p;
        }
    }
    else
    {
        pair<SSNode<M,m> *, SSNode<M,m> *> p;
        SSNode<M,m> *closestChild = node->findClosestChild(point);
        p = insertUtil(point,closestChild);
        if(p.first == nullptr)
        {
            node->updateBounding();
            return p;
        }
        else
        {
            int index = 0;
            for(int i = 0; i < node->childs.size(); i++)
            {
                if(closestChild == node->childs[i])
                {
                    index =i;
                    break;
                }
            }
            node->childs.erase(node->childs.begin()+index);
            delete closestChild;
            node->childs.push_back(p.first);
            node->childs.push_back(p.second);
            node->updateBounding();
            if(node->childs.size()<=M)
            {
                p.first = nullptr;
                p.second = nullptr;
                return p;
            }
        }
    }
    return node->split(node);
}
template<int M, int m>
void SSTree<M,m>::insert(vector<float> point)
{
    pair<SSNode<M,m> *,SSNode<M,m> *> p;
    p = insertUtil(point, root);
    vector<SSNode<M,m> *> sp;
    sp.push_back(p.first);sp.push_back(p.second);
    if(p.first!=nullptr)
    {
        vector<vector<float>> arr;
        root = new SSNode<M,m>(0,arr,sp);
        root->updateBounding();
    }
}
template<int M, int m>
pair<float, vector<float>> NearestNeighbor(SSNode<M,m> *node, vector<float> &point,
float &ndistance, vector<float> &point2)
{
    if(node->isLeaf)
    {
        int len = node->points.size();
        for(int i = 0; i < len; i++)
        {
            float dist = distance(node->points[i], point);
            if(dist < ndistance)
            {
                ndistance = dist;
                point2 = node->points[i];
            }
        }
    }
    else
    {
        vector<pair<float, SSNode<M,m> *>> sortedChildren;
        sortedChildren = node->sortByDistance(point);
        int len = sortedChildren.size();
        for(int i = 0; i < len; i++)
        {
            pair<float , SSNode<M,m>*> tmp = sortedChildren[i];
            if(tmp.first-tmp.second->radio < ndistance)
            {
                pair<float, vector<float>> answer = NearestNeighbor(tmp.second, point, ndistance, point2);
            }
        }
    }
    pair<float, vector<float>> p;
    p.first = ndistance; p.second = point2;
    return p;
}
void query_knn()
{
    //code
}
int reverseInt (int i) 
{
    unsigned char c1, c2, c3, c4;

    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;

    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}
vector<vector<float>> read_mnist(int n)
{
    vector<vector<float>> images;
    ifstream file ("t10k-images.idx3-ubyte");
    if (file.is_open())
    {
        int magic_number=0;
        int number_of_images=0;
        int n_rows=0;
        int n_cols=0;
        file.read((char*)&magic_number,sizeof(magic_number));
        magic_number= reverseInt(magic_number);
        file.read((char*)&number_of_images,sizeof(number_of_images));
        number_of_images= reverseInt(number_of_images);
        file.read((char*)&n_rows,sizeof(n_rows));
        n_rows= reverseInt(n_rows);
        file.read((char*)&n_cols,sizeof(n_cols));
        n_cols= reverseInt(n_cols);
        for(int i=0;i<n;++i)
        {
            vector<float> image;
            for(int r=0;r<n_rows;++r)
            {
                for(int c=0;c<n_cols;++c)
                {
                    unsigned char temp=0;
                    file.read((char*)&temp,sizeof(temp));
                    int pixel = (int)temp;
                    if(pixel!=0)
                        pixel=1;
                    image.push_back(pixel);
                }
            }
            images.push_back(image);
        }
    }
    return images;
}
template<int M, int m>
void knn(SSNode<M,m> *node, vector<float> point, float &ndistance, queue<pair<float,vector<float>>> &k,
int knCounter)
{
    if(node->isLeaf)
    {
        vector<vector<float>> p = node->points;
        int len = p.size();
        for(int i = 0; i < len; i++)
        {
            float dist = distance(p[i], point);
            if(dist < ndistance)
            {
                if(k.size() >=knCounter)
                {
                    pair<float, vector<float>> pair1;
                    pair1.first = dist;
                    pair1.second = p[i];
                    k.pop();
                    k.push(pair1);
                }
                else
                {
                    pair<float, vector<float>> pair1;
                    pair1.first = dist;
                    pair1.second = p[i];
                    k.push(pair1);
                }
            }
        }
    }
    else
    {
        vector<pair<float, SSNode<M,m>* >> vec1 = node->sortByDistance(point);
        int len = vec1.size();
        for(int i = 0; i < len; i++)
        {
            pair<float, SSNode<M,m> *> tmp = vec1[i];
            if(tmp.first-tmp.second->radio < ndistance)
            {
                knn(tmp.second, point,ndistance,k,knCounter);
            }
        }
    }
}

SSTree<4,2> sstree1;
vector<vector<float>> mnist = read_mnist(10000);
int build_data_structure_10k() {
  for(int i = 0; i < 10000; i++)
      sstree1.insert(mnist[i]);
  return 0;
}
int main()
{
    int option;
    cout<<"Escoga la opcion"<<endl;
    cout<<"Construir arbol con 10k elementos (1)"<<endl;
    cin>>option;
    cout<<"Indexando..."<<endl;
    if(option == 1)
    {
        Timer<int()> timed_built(build_data_structure_10k, "Index");
        timed_built();
        system("CLS");
        cout<<"Arbol creado"<<endl;
        int newOption = 1;
        while (newOption)
        {
            cout<<"Ingrese el item para buscar"<<endl;
            int item = 0;
            cin>>item;
            cout<<"Item a buscar"<<endl;
            print_mnist(mnist[item]);
            cout<<"Elemento encontrado por la funcion search de la estructura"<<endl;
            sstree1.search(sstree1.root, mnist[item]);
            cout<<"Desea continuar?(0/1)"<<endl;
            cin>>newOption;
        }
    }
    return 0;
}
