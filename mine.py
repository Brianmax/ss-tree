local damage = 50
local seconds = 10
local mayTouch = true

script.Parent.Touched:connect(function(hit)
	if hit and hit.Parent and hit.Parent:FindFirstChild("Humanoid") and mayTouch then
		hit.Parent.Humanoid.Health -= damage 
		mayTouch = false
		wait(seconds)
		mayTouch = true
	end
end)
