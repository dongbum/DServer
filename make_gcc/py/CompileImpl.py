import os, glob, time, re

HeaderList = []
NonHeaderList= []


NoneType=0;
CppType=1;
HType=2

def getlastCompileTime(Exepath) :
	if os.path.exists(Exepath) :
		lastCompileTime=os.stat(Exepath).st_mtime
	else :
		lastCompileTime=0
	return lastCompileTime

def IsCompileFile(filename) :
    # .cpp file process
    if filename[-4:] == '.cpp' :
        return CppType
    # .h file process
    elif filename[-2:] == '.h' :
        return HType
    else :
        return NoneType;

def CompileFileWrite(filepath, filename) :
    # File Write Job
    f = open(filepath, 'a')
    data = os.getcwd() + '/' + filename + '\n'
    f.write(data)
    f.close()

def CompileHeaderFileInsertList(filename) :
    HeaderList.append(filename.split('/')[-1])

def CompileNonHeaderFileInsertList(filepath) :
	NonHeaderList.append(filepath)

def FindIncludeHeader(HeaderList, filepath) :
    for headerfile in HeaderList :
        p = re.compile(headerfile, re.I | re.S)
        f = open(filepath, 'r')
        for buffer in f :
            m = p.search(buffer)
            if m:
                #print("[%s] : [%s]"%(buffer, headerfile))
                return True
    return False

       
