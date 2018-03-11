#---------------------------------------------
# Encrypt single file or crawl the entire directory
# and encrypt everything. To replace the "pub_key" below
# type: gpg --keyid-format long --list-keys your@email.null
# Usage: encrypt 'somethin g'
#---------------------------------------------
encrypt() {
python2 -c'pub_key="82B4CCC8A97E3564";
import os,shlex,shutil;from subprocess import check_output;
path_join=os.path.join;temp_list=list();
ff="'$1'";ff=(ff if not ff.endswith(os.sep) else ff[:-1]);enc="encrypted_"+ff;
def gpg(f):  check_output(shlex.split(("gpg --hidden-recipient {0}\
 --encrypt \"{1}\"".format(pub_key,f))));os.remove(f);
if os.path.isfile(ff):  shutil.copy(ff,enc);temp_list.append(enc);
else:
  if os.path.exists(enc):  shutil.rmtree(enc);
  shutil.copytree(ff,enc);
  for root,_,files in os.walk(enc):
    for x in files:
      temp_list.append(path_join(root,x)) 
print("\n\033[1;95m{0} \033[0;0m-> \033[1;94m{1}\033[0;0m\n".format(ff, enc));
[gpg(x) for x in temp_list]'
}

# The opposite action of 'encrypt'
# Grab a cup of tea and settle in.
decrypt() {
python2 -c'import os,shlex;from subprocess import check_output;
def big_mama():
  path_join=os.path.join;temp_list=list();
  ff="'$1'";ff=(ff if not ff.endswith(os.sep) else ff[:-1]);
  def gpg_decrypt(f):  check_output(shlex.split(("gpg  --quiet\
    \"{0}\"".format(f))));os.remove(f);
  if os.path.isfile(ff):  temp_list.append(ff);
  else:
    for root,_,files in os.walk(ff):
      for x in files:
        temp_list.append(path_join(root,x)) 
  [gpg_decrypt(x) for x in temp_list]
try:
  big_mama()
except Exception:
  raise SystemExit("\033[1;41m Are you trying to decrypt\
 something thats not encrypted ?\033[0;0m")'
}