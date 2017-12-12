import os,CompileImpl,Compile,sys

startpath = sys.argv[1]
LastCompileListPath = sys.argv[3]


# low path dependency -> modify filelist and headerlist
def DependencyFile(path) :
	os.chdir(path)
	pathdir = os.listdir(path)
	for each_value in pathdir :
		if os.path.isdir(each_value) :
			DependencyFile( os.getcwd() + '/' + each_value)
		else :
			FileType = CompileImpl.IsCompileFile(each_value)
			if FileType == CompileImpl.CppType :
				# file Time Check
				if os.stat(os.getcwd() + '/' + each_value).st_mtime >= CompileImpl.getlastCompileTime(sys.argv[2]) :
					CompileImpl.CompileFileWrite(LastCompileListPath, each_value[:-4])
				elif CompileImpl.FindIncludeHeader(CompileImpl.HeaderList, os.getcwd() + '/' + each_value) :
					CompileImpl.CompileFileWrite(LastCompileListPath, each_value[:-4])
	os.chdir("../")

# low path modify header , non modify header file list make
def ModifyHeaderFile(path) :
    os.chdir(path)
    pathdir = os.listdir(path)
    for each_value in pathdir :
        if os.path.isdir(each_value) :
            ModifyHeaderFile( os.getcwd() + '/' + each_value)
        else :
            FileType = CompileImpl.IsCompileFile(each_value)
            if FileType == CompileImpl.HType :
                if os.stat(os.getcwd() + '/' + each_value).st_mtime >= CompileImpl.getlastCompileTime(sys.argv[2]) :
                    CompileImpl.CompileHeaderFileInsertList(each_value)
                else :
                    CompileImpl.CompileNonHeaderFileInsertList( os.getcwd() + '/' +  each_value)
    os.chdir("../")

#header -> header include process
def DependencyHeader() :
	CompileImpl.NonHeaderList = list(set(CompileImpl.NonHeaderList))
	for each_value in CompileImpl.NonHeaderList :
		if CompileImpl.FindIncludeHeader(CompileImpl.HeaderList, each_value) :
			CompileImpl.CompileHeaderFileInsertList(each_value)

	CompileImpl.HeaderList = list(set(CompileImpl.HeaderList))

print(LastCompileListPath)
f = open(LastCompileListPath, 'w')
f.close()

if __name__ == "__main__" :
	if len(sys.argv) <= 1 :
		print('can not argv data')
	else :
		ModifyHeaderFile(startpath)
		DependencyHeader()
		DependencyFile(startpath)	
		print ('SeachCompileFile Start')


