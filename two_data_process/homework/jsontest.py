import jsonpath
import treelib
import json
import data_anla


class shujie(object):
    myid=0;
    use_pid=0;
    fir_lag=0;
    mtree = treelib.Tree()
    mtree.create_node("策略配置", 0)
    def __init__(self,data):
        super(shujie, self).__init__()
        self.data_bianli(data,self.myid,1)
    def data_bianli(self,data,id,father_type):
        dict = {}
        list = []
        if type(data)==type(dict):
            keys=data.keys()
            #对keys进行解析
            for temp in keys:
                newdata=data[temp]
                self.myid=self.myid+1;
                if(father_type==0):
                    if(self.fir_lag==1):
                        self.fir_lag=0;
                        self.mtree.create_node(str(temp),self.myid,parent=id)
                        self.use_pid=self.myid
                    else:
                        self.mtree.create_node(str(temp),self.myid,parent=self.use_pid)
                else:
                    self.mtree.create_node(str(temp), self.myid, parent=id)
                #print(self.mtree)
                self.data_bianli(newdata, self.myid, 1)
        elif type(data)==type(list):
            keys=len(data)
            temp_id=self.myid
            for i in range(keys):
                #print(data[i])
                self.fir_lag = 1;
                newdata=data[i]
                self.data_bianli(newdata,temp_id,0)
        else:
            self.fir_lag=0;
            return

testdata=data_anla.json_format_check(data_anla.data)
#testdata="{\"v\":[{\"type\":\"set_gpa\",\"frameTempMargin\":0,\"cpuUpMargin\":0,\"cpuLowMargi\":0,\"appMaxFps\":85,\"res\":0},{\"type\":\"set_fpsgo\",\"cmd_0x0206cd00\":5}]}"
print(testdata)
testdata=json.loads(testdata)






KK=shujie(testdata)
print(KK.mtree)
tree=KK.mtree
sub_tree=tree.subtree(2)
#tree.paste(sub_tree.paths_to_leaves(),sub_tree)
print(tree.to_json(with_data=True))
