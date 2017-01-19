import ConfigParser 
cf = ConfigParser.ConfigParser() 
#read config 
cf.read("data/auto.conf") 
# return all section 
secs = cf.sections() 
print 'sections:', secs 
 
opts = cf.options("cancer") 
print 'options:', opts 

kvs = cf.items("cancer") 
print 'sec_a:', kvs

d = dict.fromkeys(opts)
print d
for it in kvs:
    d[it[0]] = it[1]
print d
