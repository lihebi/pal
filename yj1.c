typedef struct tagTreeNode {
  Byte value;
  Byte leaf;
  ushort level;
  uint weight;
  struct tagTreeNode *parent;
  struct tagTreeNode *left;
  struct tagTreeNode *right;
} TreeNode;
typedef struct tagTreeNodeList {
  TreeNode *node;
  struct tagTreeNodeList *next;
} TreeNodeList;
typedef struct tagYJ1FileHeader {
  uint signature;
  uint uncompressedLength;
  uint compressedLength;
  ushort blockCount;
  Byte unknown;
  Byte huffmanTreeLength;
} YJ1FileHeader, *LpYJ1FileHeader;
typedef struct tagYJ1BlockHeader {
  ushort uncompressedLength;
  ushort compressedLength;
  ushort LzssRepeatTable[4];
  Byte LzssOffsetCodeLengthTable[4];
  Byte LzssRepeatCodeLengthTable[3];
  Byte codeCountCodeLengthTable[3];
  Byte codeCountTable[2];
} YJ1BlockHeader, *LpYJ1BlockHeader;
static uint get_bits(const void *src, uint *bitptr, uint count) {
  Byte *tmp = ((Byte)src) + ((*bitptr >> 4) << 1);
  uint bptr = *bitptr & 0xf;
  ushort mask;
  *bitptr += count;
  if (count>16-bptr) {
    count = count + bptr -16;
    mask = 0xffff >> bptr;
    return (((tmp[0] | tmp[1] << 8) & mask) << count) | ((tmp[2] | (tmp[3]<<8)) >> (16-count));
  } else {
    return (((ushort)((tmp[0] | (tmp[1] << 8)) << bptr)) >> (16 - count));
  }
}
static ushort get_loop(const void *src, uint *bitptr, LpYJ1BlockHeader header) {
  if (get_bits(src, bitptr, 1)) {
    return header->codeCountTable[0];
  } else {
    uint tmp = get_bits(src, bitptr, 2);
    if (tmp) {
      return get_bits(src, bitptr, header->codeCountCodeLengthTable[tmp-1]);
    }else {
      return header->codeCountTable[1];
    }
  }
}
static ushort get_count(const void *src, uint *bitptr, LpYJ1BlockHeader header) {
  ushort tmp;
  if ((tmp=get_bits(src, bitptr, 2)) != 0) {
    if (get_bits(src, bitptr, 1)) {
      return get_bits(src, bitptr, header->LzssRepeatCodeLengthTable[tmp-1]);
    } else {
      return SWAP16(header->LzssRepeatTable[tmp]);
    }
  } else {
    return SWAP16(header->LzssRepeatTable[0]);
  }
}
int decompress(const void *source, void *destination, int destSize) {
  LpYJ1FileHeader hdr = (LpYJ1FileHeader)source;
  Byte *src = (Byte*)source;
  Byte *dest;
  uint i;
  TreeNode *root,*node;
  do {
    ushort tree_len = ((ushort)hdr->huffmanTreeLength) * 2
    uint bitptr = 0;
    Byte *flag = (Byte)src + 16 + tree_len;
    node = root = (TreeNode*)malloc(sizeof(TreeNode) * (tree_len+1));
    root[0].leaf = 0;
    root[0].value = 0;
    root[0].left = root+1;
    root[0].right = root+2;
    for (i=1;i<=tree_len;i++) {
      root[i].leaf = !get_bits(flag, &bitptr, 1);
      root[i].value = src[15+i];
      if (root[i].leaf) {
        root[i].left = root[i].right = NULL;
      } else {
        root[i].left = root+(root[i].value<<1)+1;
        root[i].right = root[i].left +1;
      }
    }
    src += 16 + tree_len + (((tree_len & 0xf)?(tree_len>>4)+1 : (tree_len>>4)) <<1);
  } while (0);
  dest = (Byte*)destination;
  for (i=0;i<SWAP16(hdr->blockCount);i++) {
    uint bitptr;
    LpYJ1BlockHeader header;
    header = (LpYJ1BlockHeader)src;
    src+=4;
    if (!SWAP16(header->compressedLength)) {
      ushort hul = SWAP16(header->uncompressedLength);
      while(hul--) {
        *dest++ = *src++;
      }
      continue;
    }
    src += 20;
    bitptr = 0;
    for (;;) {
      ushort loop;
      if ((loop = get_loop(src, &bitptr, header)) == 0) {
        break;
      }
      while (loop--) {
        node = root;
        for (;!node->leaf;) {
          if (get_bits(src, &bitptr, 1)) {
            node = node->right;
          } else {
            node = node->left;
          }
          *dest++ = node->value;
        }
      }
      if ((loop = get_loop(src, &bitptr, header)) == 0) {
        break;
      }
      while(loop--) {
        uint pos, count;
        count = get_count(src, &bitptr, header);
        pos = get_bits(src, &bitptr, 2);
        pos = get_bits(src, &bitptr, header->LzssOffsetCodeLengthTable[pos]);
        while(count--) {
          *dest = *(dest-pos);
          dest++;
        }
      }
    }
    src = ((Byte*)header) + SWAP16(header->compressedLength);
  }
  free(root);
  return SWAP32(hdr->uncompressedLength);
}
