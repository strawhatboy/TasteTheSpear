cclog = function(...)
    print(string.format(...))
end

local LUA_TEST_MSG = "LUA TEST MSG"
local kCCNodeOnEnter = "enter"
local kCCNodeOnExit = "exit"

function __G__TRACKBACK__(msg)
    cclog("----------------------------------------")
    cclog("LUA ERROR: " .. tostring(msg) .. "\n")
    cclog(debug.traceback())
    cclog("----------------------------------------")
end

local function regNotification()
	local ccLayer = CCLayer:create();
	
	local function testNotificationHandler(obj)
		cclog("GOT MSG"  .. 1)
	end
	local function testNotificationHandler2(obj)
		cclog("GOT MSG"  .. 2)
	end
	
	local function onEnter()
		cclog("ON ENTER")
		CCNotificationCenter:sharedNotificationCenter():registerScriptObserver(ccLayer, testNotificationHandler, LUA_TEST_MSG)
		CCNotificationCenter:sharedNotificationCenter():registerScriptObserver(ccLayer, testNotificationHandler2, LUA_TEST_MSG)
	end
	
	local function onExit()
		cclog("ON EXIT")
		CCNotificationCenter:sharedNotificationCenter():unregisterScriptObserver(ccLayer, LUA_TEST_MSG)
	end
	
	local function eventHandler(eventType)
		cclog("ON EVENT: " .. eventType)
		if eventType == kCCNodeOnEnter then
			onEnter()
		elseif eventType == kCCNodeOnExit then
			onExit()
		end
	end
	
	ccLayer:registerScriptHandler(eventHandler)
	return ccLayer
end
local function regNotification2()
	local ccLayer = CCLayer:create();
	
	local function testNotificationHandler(obj)
		cclog("GOT MSG" .. 3)
	end
	local function testNotificationHandler2(obj)
		cclog("GOT MSG" .. 4)
	end
	
	local function onEnter()
		cclog("ON ENTER")
		CCNotificationCenter:sharedNotificationCenter():registerScriptObserver(ccLayer, testNotificationHandler, LUA_TEST_MSG)
		CCNotificationCenter:sharedNotificationCenter():registerScriptObserver(ccLayer, testNotificationHandler2, LUA_TEST_MSG)
	end
	
	local function onExit()
		cclog("ON EXIT")
		CCNotificationCenter:sharedNotificationCenter():unregisterScriptObserver(ccLayer, LUA_TEST_MSG)
	end
	
	local function eventHandler(eventType)
		cclog("ON EVENT: " .. eventType)
		if eventType == kCCNodeOnEnter then
			onEnter()
		elseif eventType == kCCNodeOnExit then
			onExit()
		end
	end
	
	ccLayer:registerScriptHandler(eventHandler)
	return ccLayer
end

local function main()
	cclog("LUA Main running with version: " .. _VERSION)
	local layer = regNotification()
	local layer2 = regNotification()
	local currentScene = CCDirector:sharedDirector():getRunningScene();
	currentScene:addChild(layer)
	currentScene:addChild(layer2)
	cclog("layer added.")
end

xpcall(main, __G__TRACKBACK__)