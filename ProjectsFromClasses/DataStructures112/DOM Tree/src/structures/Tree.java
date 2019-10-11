package structures;

import java.util.*;

/**
 * This class implements an HTML DOM Tree. Each node of the tree is a TagNode, with fields for
 * tag/text, first child and sibling.
 * 
 */
public class Tree {
	
	/**
	 * Root node
	 */
	TagNode root=null;
	
	/**
	 * Scanner used to read input HTML file when building the tree
	 */
	Scanner sc;
	
	/**
	 * Initializes this tree object with scanner for input HTML file
	 * 
	 * @param sc Scanner for input HTML file
	 */
	public Tree(Scanner sc) {
		this.sc = sc;
		root = null;
	}
	
	/**
	 * Builds the DOM tree from input HTML file, through scanner passed
	 * in to the constructor and stored in the sc field of this object. 
	 * 
	 * The root of the tree that is built is referenced by the root field of this object.
	 */
	public void build() {
		/** COMPLETE THIS METHOD **/
		root = recursiveBuild();
	}
	private TagNode recursiveBuild() {
		boolean hasMore = false;
		String tag = null;
		if(sc.hasNextLine()) tag = sc.nextLine();
		else return null;
		if(tag.charAt(0) == '<') {
			tag = tag.substring(1, tag.indexOf('>'));
			if(tag.charAt(0) == '/') return null;
			else hasMore = true;
		}
		TagNode temp = new TagNode(tag, null, null);
		if(hasMore) temp.firstChild = recursiveBuild();
		temp.sibling = recursiveBuild();
		return temp;
	}
	
	/**
	 * Replaces all occurrences of an old tag in the DOM tree with a new tag
	 * 
	 * @param oldTag Old tag
	 * @param newTag Replacement tag
	 */
	public void replaceTag(String oldTag, String newTag) {
		/** COMPLETE THIS METHOD **/
		recursiveReplace(root, oldTag, newTag);
	}
	private void recursiveReplace(TagNode temp, String oldTag2, String newTag2) {
		if(temp == null) return;
		if(temp.tag.equals(oldTag2)) temp.tag = newTag2;
		recursiveReplace(temp.firstChild, oldTag2, newTag2);
		recursiveReplace(temp.sibling, oldTag2, newTag2);
	}
	
	/**
	 * Boldfaces every column of the given row of the table in the DOM tree. The boldface (b)
	 * tag appears directly under the td tag of every column of this row.
	 * 
	 * @param row Row to bold, first row is numbered 1 (not 0).
	 */
//	public void boldRow(int row) {
//		/** COMPLETE THIS METHOD **/
//		if(row < 1) return;
//		recursiveBold(root, null, 1, row);
//		
//	}
//	private void recursiveBold(TagNode ptr, TagNode prev, int currentRow, int row) {
//		if(ptr == null) return;
//		if(currentRow != row) currentRow++;
//		else if(currentRow == row && ptr.firstChild == null ) {
//			prev.firstChild = new TagNode("b", ptr, null);
//		}
//		recursiveBold(ptr.firstChild, ptr, currentRow, row);
//		recursiveBold(ptr.sibling, ptr, currentRow, row);
//	}
	public void boldRow(int row) {
		if(row < 1) {
			return;
		}
		else {
			boldHelp(row, 0, root, root.firstChild);
		}
	}
	
	private void boldHelp(int row, int rowCount, TagNode prev, TagNode ptr) {
		if(ptr == null) {
			return;
		}
		if(ptr.tag.equals("tr")) {
			rowCount++;
		}
		else if(rowCount == row && ptr.firstChild == null) {
			prev.firstChild = new TagNode("b", ptr, null);
		}
		
		boldHelp(row, rowCount, ptr, ptr.firstChild);
		boldHelp(row, rowCount, ptr, ptr.sibling);
	}
	/**
	 * Remove all occurrences of a tag from the DOM tree. If the tag is p, em, or b, all occurrences of the tag
	 * are removed. If the tag is ol or ul, then All occurrences of such a tag are removed from the tree, and, 
	 * in addition, all the li tags immediately under the removed tag are converted to p tags. 
	 * 
	 * @param tag Tag to be removed, can be p, em, b, ol, or ul
	 */
	public void removeTag(String tag) {
		/** COMPLETE THIS METHOD **/
		recursiveRemove(null, root, tag);
	}

	private void recursiveRemove(TagNode prev, TagNode ptr, String tag) {
		if(ptr == null) return;
		TagNode temp = null;
		if(tag.equals("p") || tag.equals("em") || tag.equals("b") || tag.equals("ul") || tag.equals("ol")){
			if(ptr.tag.equals(tag)) {
				if(ptr.firstChild != null && ptr.firstChild.tag.equals("li")) {
					deleteLi(ptr.firstChild);
				}
				if(prev.firstChild == ptr) {
					if(ptr.sibling != null) {
						if(ptr.firstChild.sibling != null) {
							temp = ptr.firstChild;
							prev.sibling = temp;
							insertSibling(temp, ptr.sibling);
							ptr.firstChild = null;
							ptr.sibling = null;
						}
						else {
							ptr.firstChild.sibling = ptr.sibling;
							prev.firstChild = ptr.firstChild;
						}
					}
					else {
						prev.firstChild = ptr.firstChild;
					}
				}
				else if(prev.sibling != null) {
					if(ptr.sibling != null) {
						if(ptr.firstChild.sibling != null) {
							temp = ptr.firstChild;
							prev.sibling = temp;
							insertSibling(temp, ptr.sibling);
							ptr.firstChild = null;
							ptr.sibling = null;
						}
						else {
							
							ptr.firstChild.sibling = ptr.sibling;
							prev.sibling = ptr.firstChild;
						}
					}
					else {
						prev.sibling = ptr.firstChild;
					}
				}
			}
		}
		recursiveRemove(ptr, ptr.firstChild, tag);
		recursiveRemove(ptr, ptr.sibling, tag);
	}
	private void insertSibling(TagNode ptr, TagNode sibToAdd) {
		while(ptr.sibling != null) {
			ptr = ptr.sibling;
		}
		ptr.sibling = sibToAdd;
	}
	private void deleteLi(TagNode ptr) {
		if(ptr == null) return;
		if(ptr.tag.equals("li")) ptr.tag = "p";
		deleteLi(ptr.sibling);
	}
	/**
	 * Adds a tag around all occurrences of a word in the DOM tree.
	 * 
	 * @param word Word around which tag is to be added
	 * @param tag Tag to be added
	 */
	public void addTag(String word, String tag) {
		/** COMPLETE THIS METHOD **/
		recursiveAdd(word, tag, root);
	}
	private void recursiveAdd(String word, String tag, TagNode ptr) {
		if(ptr == null) return;
		recursiveAdd(word, tag, ptr.firstChild);
		
		if(ptr.firstChild != null && ptr.firstChild.tag.contains(word)) {
			String[] words = ptr.firstChild.tag.split(word);
			if(words.length == 0) {
				TagNode newTag = new TagNode(tag, ptr.firstChild, ptr.sibling);
				ptr.firstChild = newTag;
			}
			else if(words.length == 2) {
				TagNode afterWord = new TagNode(words[1], null, ptr.firstChild.sibling);
				TagNode beforeWord = new TagNode(words[0], null, null);
				TagNode original = new TagNode(word, null, null);
				TagNode newTag = new TagNode(tag, original, afterWord);
				ptr.firstChild = beforeWord;
				beforeWord.sibling = newTag;
				if(words[0].equals("")) ptr.firstChild = newTag;
			}
			else {
				if(words[0].charAt(0) == ' ') {
					TagNode original = new TagNode(word, null, null);
					TagNode newTag = new TagNode(tag, original, ptr.firstChild.sibling);
					TagNode afterWord = new TagNode(words[0], null, ptr.firstChild.sibling);
					newTag.sibling = afterWord;
					ptr.firstChild = newTag;
				}
				else {
					TagNode original = new TagNode(word, null, null);
					TagNode newTag = new TagNode(tag, original, ptr.firstChild.sibling);
					TagNode beforeWord = new TagNode(words[0], null, newTag);
					ptr.firstChild = beforeWord;
				}
				
			}
			
		}
		if(ptr.sibling != null && ptr.sibling.tag.contains(word)) {
			String[] words = ptr.sibling.tag.split(word);
			if(words.length == 0) {
				TagNode newTag = new TagNode(tag, ptr.sibling, ptr.sibling.sibling);
				ptr.sibling = newTag;
			}
			else if(words.length > 0) {
				TagNode afterWord = new TagNode(words[1], null, ptr.sibling.sibling);
				TagNode beforeWord = new TagNode(words[0], null, null);
				TagNode original = new TagNode(word, null, null);
				TagNode newTag = new TagNode(tag, original, afterWord);
				ptr.sibling = beforeWord;
				beforeWord.sibling = newTag;
				newTag.sibling = afterWord;
			}
			else {
				TagNode original = new TagNode(word, null, null);
				TagNode newTag = new TagNode(tag, original, null);
				if(words[0].charAt(0) == ' ') {
					TagNode afterWord = new TagNode(words[0], null, ptr.sibling.sibling);
					newTag.sibling = afterWord;
					ptr.sibling = newTag;
				}
				else {
					TagNode beforeWord = new TagNode(words[0], null, newTag);
					ptr.sibling = beforeWord;
				}
			}
		}
		recursiveAdd(word, tag, ptr.sibling);
		
	}
	/**
	 * Gets the HTML represented by this DOM tree. The returned string includes
	 * new lines, so that when it is printed, it will be identical to the
	 * input file from which the DOM tree was built.
	 * 
	 * @return HTML string, including new lines. 
	 */
	public String getHTML() {
		StringBuilder sb = new StringBuilder();
		getHTML(root, sb);
		return sb.toString();
	}
	
	private void getHTML(TagNode root, StringBuilder sb) {
		for (TagNode ptr=root; ptr != null;ptr=ptr.sibling) {
			if (ptr.firstChild == null) {
				sb.append(ptr.tag);
				sb.append("\n");
			} else {
				sb.append("<");
				sb.append(ptr.tag);
				sb.append(">\n");
				getHTML(ptr.firstChild, sb);
				sb.append("</");
				sb.append(ptr.tag);
				sb.append(">\n");	
			}
		}
	}
	
	/**
	 * Prints the DOM tree. 
	 *
	 */
	public void print() {
		print(root, 1);
	}
	
	private void print(TagNode root, int level) {
		for (TagNode ptr=root; ptr != null;ptr=ptr.sibling) {
			for (int i=0; i < level-1; i++) {
				System.out.print("      ");
			};
			if (root != this.root) {
				System.out.print("|----");
			} else {
				System.out.print("     ");
			}
			System.out.println(ptr.tag);
			if (ptr.firstChild != null) {
				print(ptr.firstChild, level+1);
			}
		}
	}
}
