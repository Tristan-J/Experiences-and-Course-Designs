import flash.display.MovieClip;
import flash.geom.ColorTransform;
import flash.utils.Timer;
import flash.events.TimerEvent;
import flash.events.Event;
import flash.text.TextField;

var MicroCommandStr:Object = {
		"PC+1->PC":"PC->A,S3 S2 S1 S0 /M,C0=1 DM,CPPC,SC=0000 ,SC=0010",
		"MDR->M":"MDR->B , B->ALU , ALU->MDR ,MDR->M"
	};

var opeCodeAnim:Object = {
							"M->MDR->D":[
										 [],
										 "M->MDR",
										 "MDR->D",
										 ],
							"Rj+1->Rj":[
										 [],
										 "fromRj",
										 "toRj"
										],
							
							"Rj->MAR":[
									   [],
									   "fromRj",
									   "toMAR"
									   ],
							"D->MAR":[
									  [],
									  "fromD",
									  "toMAR"
									  ],
							"D+Rj->MAR":[
										 [],
										 "fromD_NOALU",
										 "fromRj_NOALU",
										 "toMAR"
										 ],
							"SP-1->SP":[
										 [],
										 "fromSP",
										  "toSP",
									   ],
							"PC+1->PC":[
											[],
											"fromPC",
										  "toPC",
										],
							"Ri->MAR":[
									   	[],
										"fromRi",
										 "toMAR",
									   ],
							"M->MDR":[
									  [],
									  "callMemory",
									  "toMDR"
									  ],
							"MDR->C":[
									  [],
									  "fromMDR",
									  "toC",
									  ],
							"MDR->D":[
									  [],
									  "fromMDR",
									  "toD",
									  ],
							"PC->MAR":[
									   [],
									   "fromPC",
									   "toMAR"
									   ],
							"Ri->PC":[
									  [],
									  "fromRi",
									  "toPC"
									  ],
							"MDR->PC":[
									   [],
									   "fromMDR",
									   "toPC"
									   ],
							"MDR->MAR":[
										[],
										"fromMDR",
										"toMAR"
										],
							"PC+C->PC":[
										[],
										"fromPC_NOALU",
										"fromC_B_NOALU",
										"toPC"
										],
							"Ri+1->Ri":[
										[],
										"fromRi",
										"toR2"
										],
							"SP->MAR":[
									   [],
									   "fromSP",
									   "toMAR"
									   ],
							"MDR->M":[
									  [],
									  "fromMDR",
									  "callMemory"
									  ],
							"PC->MDR":[
									   [],
									   "fromPC",
									   "toMDR"
									   ],
							"C->PC":[
									 [],
									 "fromC",
									 "toPC"
									 ],
							"C->MAR":[
									  [],
									  "fromC",
									  "toMAR"
									  ],
							"gotoAndPlay2":
										[
										 [null,{},{step:200}],
										 [scene,{gotoAndPlay:2}],
										 ],
							"gotoAndPlay1":
										[
										 [null,{},{step:200}],
										 [scene,{gotoAndPlay:1}],
										 ],
							"callMemory":[
										  	[Memory_line,{color:0xFF0000}],
										  	[Memory,{gotoAndStop:2}],
										  ],
							"fromSP":[
									   [Registers.SP,{gotoAndStop:2},{step:500}],
										 [SP_line,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line6,{color:0xFF0000}],
										  "throughSelectorA",
									  ],
							"fromPC":[
									  [Registers.PC,{gotoAndStop:2},{step:500}],
										 [PC_line,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line5,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line6,{color:0xFF0000}],
										  "throughSelectorA",
									  ],
							"fromPC_NOALU":[
									  [Registers.PC,{gotoAndStop:2},{step:500}],
										 [PC_line,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line5,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line6,{color:0xFF0000}],
										  "throughSelectorA_NOALU",
									  ],
							"fromRi":[
									  	[Registers.R2,{gotoAndStop:2},{step:500}],
										 [R2_line,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line4,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line5,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line6,{color:0xFF0000}],
										 "throughSelectorB",
									  ],
							"fromR2":[
									[],
									"fromRi"
									],
							"fromRj":[
									[],
									"fromR1"
									],
							"fromRj_NOALU":[
									[],
									"fromR1_NOALU"
									],
							"fromR1":[
									  	[Registers.R1,{gotoAndStop:2},{step:500}],
										 [R1_line,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line3,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line4,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line5,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line6,{color:0xFF0000}],
										 "throughSelectorB",
									  ],
							"fromR1_NOALU":[
									  	[Registers.R1,{gotoAndStop:2},{step:500}],
										 [R1_line,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line3,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line4,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line5,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line6,{color:0xFF0000}],
										  "throughSelectorA_NOALU",
									  ],
							"fromMDR":[
									   	[Registers.MDR,{gotoAndStop:2},{step:500}],
										 [MDR_line,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line3,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line4,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line5,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line6,{color:0xFF0000}],
										 "throughSelectorB",
									   ],
							"fromPSW":[
									   	[Registers.PSW,{gotoAndStop:2},{step:500}],
										 [PSW_line,{color:0xFF0000}],
										 "throughSelectorB",
									   ],
							"fromD":[
									   	[Registers.D,{gotoAndStop:2},{step:500}],
										 [D_line,{color:0xFF0000}],
										 "throughSelectorB",
									   ],
							"fromD_NOALU":[
									   	[Registers.D,{gotoAndStop:2},{step:500}],
										 [D_line,{color:0xFF0000}],
										  "throughSelectorB_NOALU",
									   ],
							"fromC":[
									   [Registers.C,{gotoAndStop:2},{step:500}],
										 [C_line,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line6,{color:0xFF0000}],
										  "throughSelectorA",
									  ],
							"fromC_NOALU":[
									   [Registers.C,{gotoAndStop:2},{step:500}],
										 [C_line,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line6,{color:0xFF0000}],
										  "throughSelectorA_NOALU",
									  ],
							"fromC_B":[
									   [Registers.C,{gotoAndStop:2},{step:500}],
										 [C_line,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line6,{color:0xFF0000}],
										  "throughSelectorB",
									  ],
							"fromC_B_NOALU":[
									   [Registers.C,{gotoAndStop:2},{step:500}],
										 [C_line,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line6,{color:0xFF0000}],
										  "throughSelectorB_NOALU",
									  ],
							"toRi":[
									[],
									"toR2"
									],
							"toR2":[
										[Register_line.Main_line.Main_line1,{color:0xFF0000}],
										[Register_line.Main_line.Main_line2,{color:0xFF0000}],
										[Register_line.Main_line.Main_line3,{color:0xFF0000}],
										[Registers.R2,{gotoAndStop:2}],
									],
							"toR1":[
										[Register_line.Main_line.Main_line1,{color:0xFF0000}],
										[Register_line.Main_line.Main_line2,{color:0xFF0000}],
										[Registers.R1,{gotoAndStop:2}],
									],
							"toRj":[
									[],
									"toR1"
									],
							"toMAR":[
									 	[],
										"lightALUECT",
									 	[Register_line.Main_line.Main_line1,{color:0xFF0000}],
										[MAR_line,{color:0xFF0000},{step:100}],
										[Registers.MAR,{gotoAndStop:2}],
									 ],
							"toMDR":[
									 	[Register_line.Main_line.Main_line1,{color:0xFF0000}],
										[Register_line.Main_line.Main_line2,{color:0xFF0000}],
										[MDR_line,{color:0xFF0000},{step:100}],
										[Registers.MDR,{gotoAndStop:2}],
									 ],
							"toIR":[
									 	[Register_line.Main_line.Main_line1,{color:0xFF0000}],
										[Register_line.Main_line.Main_line2,{color:0xFF0000}],
										[Register_line.Main_line.Main_line3,{color:0xFF0000}],
										[IR_line,{color:0xFF0000},{step:100}],
										[Registers.IR,{gotoAndStop:2}],
									 ],
							"toSP":[
										[Register_line.Main_line.Main_line1,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line2,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line3,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line4,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line5,{color:0xFF0000}],
										 [SP_line,{color:0xFF0000},{step:100}],
										 [Registers.SP,{gotoAndStop:2}],
									],
							"toPC":[
										[],
										"lightALUECT",
										[Register_line.Main_line.Main_line1,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line2,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line3,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line4,{color:0xFF0000}],
										 [PC_line,{color:0xFF0000},{step:100}],
										 [Registers.PC,{gotoAndStop:2}],
									],
							"toPSW":[
										[Register_line.Main_line.Main_line1,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line2,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line3,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line4,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line5,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line6,{color:0xFF0000}],
										 [PSW_line,{color:0xFF0000},{step:100}],
										 [Registers.PSW,{gotoAndStop:2}],
									],
							"toC":[
										[Register_line.Main_line.Main_line1,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line2,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line3,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line4,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line5,{color:0xFF0000}],
										 [C_line,{color:0xFF0000},{step:100}],
										 [Registers.C,{gotoAndStop:2}],
									],
							"toD":[
										[Register_line.Main_line.Main_line1,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line2,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line3,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line4,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line5,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line6,{color:0xFF0000}],
										 [D_line,{color:0xFF0000},{step:100}],
										 [Registers.D,{gotoAndStop:2}],
									],
							"throughSelectorA":
										[
										 [Register_line.Main_line.Main_line7,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line9,{color:0xFF0000},{step:500}],
										 [LEFT.SelectorA,{gotoAndStop:2},{step:500}],
										 [SelectorA_ALU_line,{color:0xFF0000}],
										 [LEFT.ALU,{gotoAndStop:2},{step:500}],
										 [Shifter_ALU_line,{color:0xFF0000}], 
										 [LEFT.Shifter,{gotoAndStop:2},{step:500}],
										 [Register_line.Shifter_line,{color:0xFF0000}],
										],
							"lightALUECT":
										[
										 [LEFT.ALU,{gotoAndStop:2},{step:500}],
										 [Shifter_ALU_line,{color:0xFF0000}], 
										 [LEFT.Shifter,{gotoAndStop:2},{step:500}],
										 [Register_line.Shifter_line,{color:0xFF0000}],
										 ],
							"throughSelectorB":
										[
											[Register_line.Main_line.Main_line7,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line8,{color:0xFF0000},{step:500}],
										 [LEFT.SelectorB,{gotoAndStop:2},{step:500}],
										 [SelectorB_ALU_line,{color:0xFF0000}],
										 [LEFT.ALU,{gotoAndStop:2},{step:500}],
										 [Shifter_ALU_line,{color:0xFF0000}], 
										 [LEFT.Shifter,{gotoAndStop:2},{step:500}],
										 [Register_line.Shifter_line,{color:0xFF0000}],
										],
							"throughSelectorA_NOALU":
										[
										 [Register_line.Main_line.Main_line7,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line9,{color:0xFF0000},{step:500}],
										 [LEFT.SelectorA,{gotoAndStop:2},{step:500}],
										 [SelectorA_ALU_line,{color:0xFF0000}],
										],
							"throughSelectorB_NOALU":
										[
											[Register_line.Main_line.Main_line7,{color:0xFF0000}],
										 [Register_line.Main_line.Main_line8,{color:0xFF0000},{step:500}],
										 [LEFT.SelectorB,{gotoAndStop:2},{step:500}],
										 [SelectorB_ALU_line,{color:0xFF0000}],
										]
						  };					
					

var config_index:int = 0;
var single_index:int = 0;

function displayMicroCommand(textH:TextField,c:String):void
{
	if(MicroCommandStr[c]!=null)
		textH.text = MicroCommandStr[c];
	else 
		textH.text = MicroCommandStr["null"];
}

function parseOperatorCode(codes:Array)
{
	var configArr:Array = [];
	
	for each(var code:String in codes)
	{
		if(opeCodeAnim[code]!=null)
		{
			configArr.push(opeCodeAnim[code]);
		}
	}
	//trace(configArr);
	parseConfig(configArr);
}

function parseConfig(config:Array):void
{
	if(config_index>=config.length)
		return;
	single_index = 0;
	var group:Array = config[config_index];
	config_index++;
	groupAction(group,config);
}

function groupAction(group:Array,config:Array):void
{
	if(single_index>=group.length)
	{
		parseConfig(config);
		return;
	}

	if(group[single_index] is String)
	{
		replace_why(group,single_index,opeCodeAnim[group[single_index]]);
		single_index--;
	}
	var single:Array = group[single_index];
	single_index++;
	if(single==null)
		return;
	objAction(single[0],single[1]);
	sysAction(single[2],group,config);
}

function replace_why(dest:Array,index:int,src:Array):void
{
	dest.splice(index,1);
	for each(var obj:Object in src)
	{
		dest.splice(index-1,0,obj);
		index++;
	}
}

function sysAction(actions:Object,group:Array,config:Array):void
{
	if(actions==null)
	{
		actions = {step:0};
	}
	for(var action:String in actions)
	{
		switch(action)
		{
			
		}
	}
	
	var timer:Timer = new Timer(actions['step'],1);
	timer.addEventListener(TimerEvent.TIMER,function(e:Event){
							 groupAction(group,config);
							  });
	timer.start();
}

function objAction(obj:MovieClip,actions:Object):void
{
	if(obj==null)
		return;
	for(var action:String in actions)
	{
		switch(action)
		{
			case "color":
				lightUp(obj,actions[action]);
				break;
			case "gotoAndStop":
				obj.gotoAndStop(actions[action]);
				break;
			case "gotoAndPlay":
				obj.gotoAndPlay(actions[action]);
				break;
		}
	}
}

function lightUp(obj:MovieClip,color:uint):void
{
	var colorInfo:ColorTransform = obj.transform.colorTransform;
	colorInfo.color = color;
	obj.transform.colorTransform = colorInfo;
}

