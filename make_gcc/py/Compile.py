import os,CompileImpl,sys

startpath = sys.argv[1]
CompileListPath = sys.argv[3] 

def LowPathAllFile(path) :
    os.chdir(path)
    pathdir = os.listdir(path)
    for each_value in pathdir :
        if os.path.isdir(each_value) :
            LowPathAllFile( os.getcwd() + '/' + each_value)
        else :
            FileType = CompileImpl.IsCompileFile(each_value)
            if FileType == CompileImpl.CppType :
                CompileImpl.CompileFileWrite(CompileListPath, each_value[:-4])
            elif FileType == CompileImpl.HType :
                if os.stat(os.getcwd() + '/' + each_value).st_mtime >= CompileImpl.getlastCompileTime(sys.argv[2]) :
                    CompileImpl.CompileHeaderFileInsertList(each_value)
                else :
                    CompileImpl.CompileNonHeaderFileInsertList( os.getcwd() + '/' +  each_value)
    os.chdir("../")




f = open(CompileListPath, 'w')
f.close()

if __name__ == "__main__" :
	if len(sys.argv) <= 1 :
		print('not argv data')
	else :
		LowPathAllFile(startpath + '/src')




