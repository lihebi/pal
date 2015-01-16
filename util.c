// NO NEED
int MKF_get_chunk_count(FILE *fp) {
  int count;
  fseek(fp, 0, SEEK_SET);
  fread(&count, sizeof(int), 1, fp);
  count = (SWAP32(count)-4)/4;
  return count;
}
// get the size of a chunk in an MKF archive
int MKF_get_chunk_size(uint chunkId, FILE *fp) {
  uint offset = 0;
  uint nextOffset = 0;
  // uint chunkCount = 0;
  // chunkCount = MKF_get_chunk_count(fp);
  // if (chunkId >= chunkCount) {
  //   return -1;
  // }
  fseek(fp, 4*chunkId, SEEK_SET);
  fread(&offset, sizeof(uint), 1, fp);
  fread(&nextOffset, sizeof(uint), 1, fp);
  offset = SWAP32(offset);
  nextOffset = SWAP32(nextOffset);
  return nextOffset-offset;
}
int MKF_read_chunk(char *buffer, uint size, uint chunkId, FILE *fp) {
  uint offset = 0;
  uint nextOffset = 0;
  // uint chunkCount;
  uint chunkLen;
  // chunkCount = MKF_get_chunk_count(fp);
  // if (chunkId >= chunkCount) {
  //   return -1;
  // }
  fseek(fp, 4*chunkId, SEEK_SET);
  fread(&offset, 4, 1, fp);
  fread(&nextOffset, 4, 1, fp);
  offset = SWAP32(offset);
  nextOffset = SWAP32(nextOffset);
  chunkLen = nextOffset - offset;
  fseek(fp, offset, SEEK_SET);
  fread(buffer, chunkLen, 1, fp);
  return (int)chunkLen;
}
