<?xml version="1.0" encoding="ISO-8859-1"?>
<!-- Generated	by NCL Eclipse -->
<ncl id="causalConnBase" xmlns="http://www.ncl.org.br/NCL3.0/EDTVProfile">
	<head>
		<connectorBase>
			<causalConnector id="onBeginResume">
				<simpleCondition role="onBegin"/>
				<simpleAction role="resume" max="unbounded" qualifier="par"/>
			</causalConnector>
			<causalConnector id="onEndResume">
				<simpleCondition role="onEnd"/>
				<simpleAction role="resume" max="unbounded" qualifier="par"/>
			</causalConnector>
			<causalConnector id="onBeginPause">
				<simpleCondition role="onBegin"/>
				<simpleAction role="pause" max="unbounded" qualifier="par"/>
			</causalConnector>
			<causalConnector id="onEndPause">
				<simpleCondition role="onEnd"/>
				<simpleAction role="pause" max="unbounded" qualifier="par"/>
			</causalConnector>
			<causalConnector id="onBeginAbort">
				<simpleCondition role="onBegin"/>
				<simpleAction role="abort" max="unbounded" qualifier="par"/>
			</causalConnector>
			<causalConnector id="onEndAbort">
				<simpleCondition role="onEnd"/>
				<simpleAction role="abort" max="unbounded" qualifier="par"/>
			</causalConnector>
		
			<causalConnector id="onBeginStart">
				<simpleCondition role="onBegin"/>
				<simpleAction role="start" max="unbounded" qualifier="par"/>
			</causalConnector>
			<causalConnector id="onEndStart">
				<simpleCondition role="onEnd"/>
				<simpleAction role="start" max="unbounded" qualifier="par"/>
			</causalConnector>
			<causalConnector id="onBeginStartSeq">
				<simpleCondition role="onBegin"/>
				<simpleAction role="start" max="unbounded" qualifier="seq"/>
			</causalConnector>
			<causalConnector id="onBeginStartDelay">
				<connectorParam name="delay"/>
				<simpleCondition role="onBegin"/>
				<simpleAction role="start" delay="$delay" max="unbounded" qualifier="par"/>
			</causalConnector>
			<causalConnector id="onEndStop">
				<simpleCondition role="onEnd"/>
				<simpleAction role="stop" max="unbounded" qualifier="par"/>
			</causalConnector>
			<causalConnector id="onBeginStop">
				<simpleCondition role="onBegin"/>
				<simpleAction role="stop" max="unbounded" qualifier="par"/>
			</causalConnector>
			<causalConnector id="onBeginSetStart">
				<connectorParam name="var"/>
				<simpleCondition role="onBegin"/>
				<compoundAction operator="seq">
					<simpleAction role="set" max="unbounded" value="$var"/>
					<simpleAction role="start" max="unbounded" qualifier="par"/>
				</compoundAction>	
			</causalConnector>
			<causalConnector id="onKeySelectionStopSetStart">
				<connectorParam name="varSet"/>
				<connectorParam name="keyCode"/>					
				<simpleCondition role="onSelection" key="$keyCode"/>
				<compoundAction operator="seq">
					<simpleAction role="stop" max="unbounded" qualifier="par"/>	
					<simpleAction role="set" max="unbounded" value="$varSet"/>
					<simpleAction role="start" max="unbounded" qualifier="par"/>									
				</compoundAction>				
			</causalConnector>
			<causalConnector id="onKeySelectionSetStart">
				<connectorParam name="varSet"/>
				<connectorParam name="keyCode"/>					
				<simpleCondition role="onSelection" key="$keyCode"/>
				<compoundAction operator="seq">					
					<simpleAction role="set" max="unbounded" value="$varSet"/>
					<simpleAction role="start" max="unbounded" qualifier="par"/>									
				</compoundAction>				
			</causalConnector>
			<causalConnector id="onKeySelectionSetStop">
				<connectorParam name="varSet"/>
				<connectorParam name="keyCode"/>					
				<simpleCondition role="onSelection" key="$keyCode"/>
				<compoundAction operator="seq">					
					<simpleAction role="set" max="unbounded" value="$varSet"/>
					<simpleAction role="stop" max="unbounded" qualifier="par"/>									
				</compoundAction>				
			</causalConnector>
			<causalConnector id="onKeySelectionSetStopDelay">
				<connectorParam name="varSet"/>
				<connectorParam name="delay"/>
				<connectorParam name="keyCode"/>					
				<simpleCondition role="onSelection" key="$keyCode"/>
				<compoundAction operator="seq">		
					<simpleAction role="set" max="unbounded" value="$varSet"/>			
					<simpleAction role="stop" delay="$delay" max="unbounded" qualifier="par"/>		
				</compoundAction>
				
			</causalConnector>
			<causalConnector id="onEndSet">
				<connectorParam name="varSet"/>
				<simpleCondition role="onEnd"/>
				<simpleAction role="set" value="$varSet" max="unbounded"/>				
			</causalConnector>
			<causalConnector id="onKeySelectionStopStart">
				<connectorParam name="keyCode"/>				
				<simpleCondition role="onSelection" key="$keyCode"/>
				<compoundAction operator="seq">
					<simpleAction role="stop" max="unbounded" qualifier="par"/>
					<simpleAction role="start" max="unbounded" qualifier="par"/>					
				</compoundAction>	
			</causalConnector>
			<causalConnector id="onKeySelectionStop">
				<connectorParam name="keyCode"/>				
				<simpleCondition role="onSelection" key="$keyCode"/>
				<compoundAction operator="seq">
					<simpleAction role="stop" max="unbounded" qualifier="par"/>								
				</compoundAction>	
			</causalConnector>
			<causalConnector id="onKeySelectionStart">
				<connectorParam name="keyCode"/>				
				<simpleCondition role="onSelection" key="$keyCode"/>				
				<simpleAction role="start" max="unbounded" qualifier="par"/>				
			</causalConnector>
			<causalConnector id="onKeySelectionAbort">
				<connectorParam name="keyCode"/>				
				<simpleCondition role="onSelection" key="$keyCode"/>				
				<simpleAction role="abort" max="unbounded" qualifier="par"/>				
			</causalConnector>
			<causalConnector id="onKeySelectionPause">
				<connectorParam name="keyCode"/>				
				<simpleCondition role="onSelection" key="$keyCode"/>				
				<simpleAction role="pause" max="unbounded" qualifier="par"/>				
			</causalConnector>
			<causalConnector id="onKeySelectionResume">
				<connectorParam name="keyCode"/>				
				<simpleCondition role="onSelection" key="$keyCode"/>				
				<simpleAction role="resume" max="unbounded" qualifier="par"/>				
			</causalConnector>
			<causalConnector id="onSelectionStopStart">
				<simpleCondition role="onSelection"/>
				<compoundAction operator="seq">
					<simpleAction role="stop" max="unbounded" qualifier="par"/>
					<simpleAction role="start" max="unbounded" qualifier="par"/>					
				</compoundAction>	
			</causalConnector>
			<causalConnector id="onKeySelectionSet">
				<connectorParam name="keyCode"/>
				<connectorParam name="varSet"/>									
				<simpleCondition role="onSelection" key="$keyCode"/>
				<simpleAction max="unbounded" role="set" value="$varSet"/>				
			</causalConnector>
			<causalConnector id="onBeginVarStart">
				<compoundCondition operator="and">
					<simpleCondition role="onBegin"/>
					<assessmentStatement comparator="eq">
						<attributeAssessment role="var" attributeType="nodeProperty" eventType="attribution"/>
						<valueAssessment value="true"/>
					</assessmentStatement>
				</compoundCondition>
				<simpleAction role="start" max="unbounded"/>
			</causalConnector>	
			<causalConnector id="onBeginStartSetDelay">
				<connectorParam name="var"/>
				<connectorParam name="delay"/>				
				<connectorParam name="duration"/>
				<simpleCondition role="onBegin"/>
				<compoundAction operator="seq">
					<simpleAction role="start" max="unbounded"/>
					<simpleAction role="set" max="unbounded" value="$var" delay="$delay" duration="$duration"/>
				</compoundAction>	
			</causalConnector>
			<causalConnector id="onSelectionSetStop">
				<connectorParam name="var"/>
				<simpleCondition role="onSelection"/>
				<compoundAction operator="seq">
					<simpleAction role="set" value="$var" max="unbounded" qualifier="par"/>
					<simpleAction role="stop" max="unbounded"/>	
				</compoundAction>				
			</causalConnector>
			<causalConnector id="onOrSelectionSetStopStart">
				<connectorParam name="var"/>
				<simpleCondition role="onSelection" qualifier="or" max="unbounded"/>
				<compoundAction operator="seq">
					<simpleAction role="set" value="$var" max="unbounded" qualifier="par"/>
					<simpleAction role="stop" max="unbounded"/>
					<simpleAction role="start" max="unbounded"/>
				</compoundAction>
			</causalConnector>			
			<causalConnector id="onBeginSet">
				<connectorParam name="varSet"/>
				<simpleCondition role="onBegin"/>
				<simpleAction role="set" value="$varSet" max="unbounded"/>				
			</causalConnector>
			<causalConnector id="onEndSetStopDelay">
				<connectorParam name="var"/>
				<simpleCondition role="onEnd"/>
				<compoundAction operator="seq">
				    <simpleAction role="set" value="$var" max="unbounded"/>				
					<simpleAction role="stop" max="unbounded" qualifier="par" delay="3s"/>
				</compoundAction>
			</causalConnector>
		</connectorBase>
	</head>
</ncl>
