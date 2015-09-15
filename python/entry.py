import image
import os

nums = []
for root, dir, files in os.walk("./images"):
	for i in files:
		print root, dir, i
		nums.append(image.process(root+"/"+i))

print "Numbers"
print "\n".join(nums)