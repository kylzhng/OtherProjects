package lse;
import java.util.*;
import java.io.*;

public class Search {

	public static void main(String args[]) throws IOException {
        String docsFile = "docs.txt";
        String noiseWords = "noisewords.txt";

        LittleSearchEngine searchEngine = new LittleSearchEngine();

        searchEngine.makeIndex(docsFile, noiseWords);

        String kw1 = "true";
        String kw2 = "";

        System.out.println(searchEngine.top5search(kw1, kw2));
		
//		LittleSearchEngine lse=new LittleSearchEngine();
//		try {
//			lse.makeIndex("docs.txt", "noisewords.txt");
//			System.out.println("Top Five Search: ");
//			System.out.println(lse.top5search("deep", "world"));
//			System.out.println();
//			System.out.println("Get Keyword: ");
//			System.out.println(lse.getKeyword("deep"));
//			System.out.println();
//			
//			System.out.println("Keywords Index: ");
//			for (String hi : lse.keywordsIndex.keySet())
//				System.out.println(hi+" "+lse.keywordsIndex.get(hi));
//			
//		} catch (FileNotFoundException e) {
//			e.printStackTrace();
//		}
        
        
    }
}
