
local GameManager = class("GameManager")

GameManager.qiListTable={}
GameManager.qiSumTable={}
GameManager.lastRwdTable={}
GameManager.curQi="20181016001"
GameManager.curQiTime=60
--------------------------------------

function GameManager.loadQiDetailTable()
    for i=1,#dict_QiDetailTable do
        local oneQi = {
            qi=dict_QiDetailTable[i].qi,
            num1=dict_QiDetailTable[i].num1,
            num2=dict_QiDetailTable[i].num2,
            num3=dict_QiDetailTable[i].num3,
            num4=dict_QiDetailTable[i].num4,
            num5=dict_QiDetailTable[i].num5,
            num6=dict_QiDetailTable[i].num6,
            num7=dict_QiDetailTable[i].num7,
            num8=dict_QiDetailTable[i].num8,
        }
        table.insert(GameManager.qiListTable,oneQi)
    end
    -- dump(dict_QiDetailTable,"dict_QiDetailTable")
    GameManager.setQiSumTable()
    GameManager.setLastRwdTable()
end

function GameManager.setQiSumTable()
    GameManager.qiSumTable={}
    for i=1,20 do
        local rwdCnt = 0
        local missCnt = 0
        local maxMissCnt = 0
        local pos = dict_FruitTable[tostring(i)].pos
        for j=1,#dict_QiDetailTable do
            local hit = false
            for k=1,8 do
                if dict_QiDetailTable[j]["num"..tostring(k)]==tostring(i) then
                    hit = true
                    break
                end
            end
            if hit then
                rwdCnt=rwdCnt+1
                missCnt = 0
            else
                missCnt = missCnt+1
                if missCnt>maxMissCnt then
                    maxMissCnt=missCnt
                end
            end
        end
        local sunInfo = {
            rwdCnt=rwdCnt,
            maxMissCnt=maxMissCnt,
            pos=pos,
        }
        table.insert(GameManager.qiSumTable,sunInfo)
    end
    dump(GameManager.qiSumTable,"GameManager.qiSumTable")
end

function GameManager.setLastRwdTable()
    GameManager.lastRwdTable={}
    local lastIdx = #dict_QiDetailTable
    if lastIdx>0 then
        GameManager.lastRwdTable={
            qi=dict_QiDetailTable[lastIdx].qi,
            num1=dict_QiDetailTable[lastIdx].num1,
            num2=dict_QiDetailTable[lastIdx].num2,
            num3=dict_QiDetailTable[lastIdx].num3,
            num4=dict_QiDetailTable[lastIdx].num4,
            num5=dict_QiDetailTable[lastIdx].num5,
            num6=dict_QiDetailTable[lastIdx].num6,
            num7=dict_QiDetailTable[lastIdx].num7,
            num8=dict_QiDetailTable[lastIdx].num8,
            total=12345,
            rwdType1={
                _type=0,
                _value=25,
            },
            rwdType2={
                _type=0,
                _value=5,
            },
            rwdType3={
                _type=0,
                _value=8,
            },
            rwdType4={
                _type=0,
                _value=31,
            },
            rwdType5={
                _type=0,
                _value=62,
            },
        }
    end
        
end

-- table.insert(GameManager.BetListTable,oneBet)
-- table.remove(GameManager.BetListTable, curIdx);
return GameManager




