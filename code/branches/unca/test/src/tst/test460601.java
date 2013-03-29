import java.net.*;
import java.io.*;
import java.util.*;

	public class test460601 {

	/**
	 * @param args
	 */
	public static void main(String[] args) throws Exception{
//		FileWriter resultFile = new FileWriter(new File("./result"));
		StringBuffer request = new StringBuffer();
		request.append("@")
				.append("186  ")
				.append("130325130325000005"+args[0])
				.append(" ")
				.append("010202")
				.append("00")
				.append("13073010695         ")
				.append("1")
				.append("000010")
				.append("C539D4D157C046A9                ")
				.append("00001")
				.append("1")
				.append("00000")
				//.append("50        ")
				.append("0000000050")
				.append("066000000501        ")
				.append("4BE65F6E88E0C367                ")
				.append("13032513032500000542"+(char)26);
		
		BufferedReader in = null; /* receive */
		PrintWriter out = null; /* send */
		Socket soc = new Socket("130.51.15.102", 8119);
		in = new BufferedReader(new InputStreamReader(soc.getInputStream()));
		out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(soc
				.getOutputStream())), true);
		long start = System.currentTimeMillis();
		System.out.println(request.toString());
		out.print(request.toString());
//		FileWriter.println(request);
		out.flush();
		int response=-1;

		Thread.sleep(100);
		System.out.println("close?:"+soc.isClosed());
		System.out.println("connect?:"+soc.isConnected());
		System.out.println("input?:"+soc.isInputShutdown());
		System.out.println("output?:"+soc.isOutputShutdown());
		StringBuffer responseBuffer = new StringBuffer();
		char tmp;
		do{
			
			tmp=(char)in.read();
			responseBuffer.append(tmp);
		} while(tmp!=((char)26));
		System.out.println(responseBuffer.toString());
//		FileWriter.println(responseBuffer.toString());
		System.out.println("close?:"+soc.isClosed());
		System.out.println("connect?:"+soc.isConnected());
		System.out.println("input?:"+soc.isInputShutdown());
		System.out.println("output?:"+soc.isOutputShutdown());
		System.out.println(System.currentTimeMillis()-start);
	}
}
